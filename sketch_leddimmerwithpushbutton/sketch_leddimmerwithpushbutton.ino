#include <EEPROM.h>
#include "leddimmerwithpushbutton.h"

#include "wiring_private.h"
#include "pins_arduino.h"
/*

Dual led dimmer with push button control, using Adafruit Trinket (ATTiny85).
If the button is pushed for a short time (<1 second), the light wil toggle on/off.
If the button is held for a longer time (>1 second), the dimming function comes in action
and will decrease/increase the intensity of the led (via Pulse Width Modulation).

Circuit:

GPIO#4:
Dimmer: output PWM light 1 NO, leds will flicker on startup
Boot: B4, OC1B output PWM. This pin is used for USB programming.
Disadavantage of double use of this output pwm (OCR0B): leds will flicker
during programming.

GPIO#3 PB3, OC1B(inv), output PWM?
Dimmer: Light 2
Boot: This pin is used for USB programming.

GPIO#2 PB2
Dimmer: input button for light 1

GPIO#1 PB1 OC1A output PWM (Pulse Width Modulation),
Dimmer: use onboard led to signal key press and eeprom store (after some seconds)
connected to onboard led, (like pin 13 on a regular Arduino)

GPIO#0 PB0 OC1A(inv) output PWM.
Dimmer: light 1

Input buttons are connected to GND and with a resistor (1k) to the input pins.

Output PWM are connected to N-channel HEXFET, so high output will light the leds.

Dimmer pin layout summary as of Date 20140517
Function   Pin           Comments
Button1    PB2
Button2    PB4           With 1k resistor in series to avoid short circuit at boot time
Light1     PB0=OC1A(inv) Inverted, software must handle this
Light2     PB3=OC1B(inv) Inverted, software must handle this


Trinket board modifications:
Remove D1 and D3 zener diodes and R3 resistor. otherwise pins will not work as digital input.

Programming:
Use Adafruit IDE (based on Arduino IDE version 1.0.5). Don't know whether that is necessary, but it has all
definitions for the ATTiny85 already installed.
I used an Arduino Leonardo as ISP to program the Adafruit Trinket. After the modification of the Trinket
the program load via the Trinket USB port doesn't work anymore, so you have to fall-back to ISP programming.
It is not desirable to leave the Trinket USB boot loader in place anyway, because the Trinket will try to USB-boot
at startup, which will make your led light flicker.
There are many sources on how to do this, mainly using Arduino Uno. Using an Arduino Leonardo is a little bit more
difficult, but also quite well described on internet.
*/

#define button1Pin 2
#define button2Pin 4
#define led1Pin 0
#define led2Pin 3

// Looptime in ms
#define LOOPTIME 10
// Fade-out time (when turning light off, how long will it fade out, in ms)
// A nice value is 3000 ms (3 seconds) if you want a fade out.
// I don't like the flickering fade-out.
#define FADEOUTTIME 0
// If the button is pressed shorter than onOffButtonTime, the
// on/off status of the led is toggled. Unit is 10ms.
#define onOffButtonTime 100 /* in units of 10ms */

// The number of loops when the increment/decrement brightness is adjusted 
#define stepsSpeed1 100

Light light1={led1Pin,0,0,0,0,0,0L,0};
Light light2={led2Pin,10,0,0,0,0,0L,0};
Button button1={button1Pin,HIGH,HIGH,0,0};
Button button2={button2Pin,HIGH,HIGH,0,0};

// The constant for calculating the fade-out
const float k=6.2146081 / ((float)FADEOUTTIME/(float)LOOPTIME);

// analogWrite to control the inversed pins.
//
void myAnalogWrite(void *l)
{
  Light *light;
  light=(Light *)l;
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.
        int val;
        uint8_t pin=light->pin;
        val=light->brightness;
        // But if light is off, override the value
        if ((light->state==0) && (light->lightOn==0)) {
          if ((light->cyclesInThisState * LOOPTIME) < FADEOUTTIME) {
            // fade out. Formula: val= e ^^ (-k*t)
            // For t=FADEOUTTIME, val should be 1/512 (half bit), so k=- ln(0.002) / FADEOUTTIME
            
            val=(byte) ( ((float)light->brightness)* pow(2.7182818,-k * (float)light->cyclesInThisState));
          } else {
            // fade out time has expired, turn light off completely
            val=0;
          }
        }
        // If we use the inverse pins, the brightness must be inverted
        if ((pin==0) || (pin==3)) {
          val=255 - val;
        }
	{
          // Only support ATTiny pins.
          // Pin 0=PB0=OC1A(inv)
          // Pin 1=PB1=OC1A  (with on-board led)
          // Pin 3=PB3=OC1B(inv)
          // Pin 4=PB4=OC1B
          // connect pwm to pin on timer 1, channel B
          switch (pin) {
            case 0: // PB0=OC1A(inv)
              OCR1A=val;
              break;
            case 1: // on-board led
              //sbi(TCCR1,COM1A1);
              OCR1A=val;
              break;
            case 3:
              //sbi(TCCR1,COM1B0); // inverted output
              OCR1B = val;
              break;
            case 4:
              //sbi(TCCR1,COM1B1); // clear on compare
              OCR1B = 20; //val;
              break;
          } // end switch
	}
} // myAnalogWrite



// Stupid Arduino IDE makes me use a void pointer as intermediate.
// See: http://forum.arduino.cc/index.php/topic,41848.0.html
void setupButton(void *b) {
  Button *button;
  button=(Button *)b;
  // pull up resistor enable for button inputs PB0 and PB2
  //pinMode(button->pin,INPUT);
  //digitalWrite(button->pin,HIGH);
  
  cbi(DDRB,button->pin); // input mode
  sbi(PORTB,button->pin); // enable pull-up resistor
}
void setupLight(void *l) {
  Light *light;
  light=(Light *)l;
  // Read eeprom values
  // They might be invalid (e.g. at first start), but that is not very
  // important, but try a little bit.
  // byte 0: 55 means valid, any other value: invalid
  // byte 1: the value for lightOn
  // byte 2: the value for brightness
  // byte 10 ... repeated for next light
  int index; //offset in eeprom
  index=light->eepromOffset;
  if (EEPROM.read(index++)==55) {
    light->lightOn=EEPROM.read(index++);
    light->brightness=EEPROM.read(index++);
    light->brightnessDirection=EEPROM.read(index++);
  }
  light->state=0;
  // simulate as if we are already a long time in this state
  light->cyclesInThisState=FADEOUTTIME*LOOPTIME+100;

          // Only support ATTiny pins.
          // Pin 0=PB0=OC1A(inv)
          // Pin 1=PB1=OC1A  (with on-board led)
          // Pin 3=PB3=OC1B(inv)
          // Pin 4=PB4=OC1B
          // connect pwm to pin on timer 1, channel B
          switch (light->pin) {
            case 0: // PB0=OC1A(inv)
              
              cbi(TCCR1,COM1A1);
              sbi(TCCR1,COM1A0); // enable inverted output
              //analogWrite(1,val); //debug
              //analogWrite(0,val); //debug
              //digitalWrite(0,200);
              OCR1A=255; // Turn off light at startup to avoid flickering
              pinMode(1,OUTPUT); // DEBUG
              break;
            case 3:
              cbi(GTCCR,COM1B1);
              sbi(GTCCR,COM1B0); // inverted output
              OCR1B = 127; // Turn off light at startup to avoid flickering
              break;
            case 4:
              sbi(TCCR1,COM1B1); // clear on compare
              OCR1B = 0; // Turn off light at startup to avoid flickering
              break;
          } // end switch
  //pinMode(light->pin,OUTPUT);
  sbi(DDRB,light->pin);
  sbi(TCCR1,PWM1A); // ENABLE Pulse Width Modulation
  sbi(GTCCR,PWM1B);
} // setupLight

void setup() {
  setupButton(&button1);
  setupButton(&button2);

  setupLight(&light1);
  setupLight(&light2);
}

// This function is called for every loop voor every light
/*
states:
0: stable (on/off, or stable brightness)
1: button pressed, first period, onOffButtonTime, if button is released in this state, on/off is toggled and go to state 0.
   if time-out, turn light on, set brightness to 0, set brightnessDirection to 1, go to state 2
2: brightness adjust slowly (timePerStep1), depending on brightnessDirection. If timePressed exceeds stepsSpeed1, adjust timePerStep2
*/
void loopLight(void *l,void *b) {
  Button *button;
  button=(Button *)b;
  Light *light;
  light=(Light *)l;
  if (button->outValue==LOW) {
    // button is pressed, so some action is going on
    //pinMode(1,OUTPUT); // turn on monitor led
    //sbi(DDRB,1);
    sbi(DDRB,1); // turn on on-board led on Trinket board
    switch (light->state) {
      case 0:
        // do nothing
        light->state=1; // button pressed
        break;
      case 1:
        // wait for a while for a release of the button,
        // that would toggle on/off
        // if time-out, then goto state 2
        if (button->timePressed>onOffButtonTime) {
          // end of state 1
          light->state=2;
        }
        break;
      case 2:
        // Button was pressed longer than about 1 second.
        // put light on
        light->lightOn=1;
        if (light->brightnessDirection==0) {
          // 0 is illegal value
          light->brightnessDirection=1;
        }
        // Method 2: if brightness is high, then accelerate faster
        int stepsPerCycle=(light->brightness / 80)+1;
        int timePerStep=4 - (light->brightness / 20);
        if (timePerStep<1) {
          timePerStep=1;
        }
        // Method 3 todo
        //float dimSpeed;
        //timePerStep=1;
        // temporary int as brightness to detect overflow in an easier way
        int b=light->brightness;
        if ((button->timePressed % timePerStep) == 0 ) {
          b+=(stepsPerCycle*light->brightnessDirection);
        }
        if (b>255) {
          // oops, overflow, so change direction
          b=255; // max value
          light->brightnessDirection=-1;
        }
        if (b<12) {
          // oops, underflow, so change direction
          b=12;
          light->brightnessDirection=1;
        }
        // Store the temporary value in the real light struct
        light->brightness=b;
        break;
    }
  } else {
    // button not pressed
    switch (light->state) {
      case 0:
        // button not pressed, in approx. 5 seconds, save state
        if (light->cyclesInThisState==500) {
          // save state, check whether there was a change in any data
          int index; //offset in eeprom
          int base;
          base=light->eepromOffset; // the isValid byte, 55 means valid data, other values mean invalid data in eeprom
          index=base+1; // first data byte
          if (light->lightOn!=EEPROM.read(index)) {
            // should write
            if (EEPROM.read(base)==55) {
              // Indicate data is invalid/inconsistent (lightOn, brightness, brihtnessDirection)
              EEPROM.write(base,73);
            }
            // save the value
            EEPROM.write(index,light->lightOn);
          }
          index++;
          if (light->brightness!=EEPROM.read(index)) {
            // should write
            if (EEPROM.read(base)==55) {
              // Indicate data is invalid/inconsistent (lightOn, brightness, brihtnessDirection)
              EEPROM.write(base,73);
            }
            // save the value
            EEPROM.write(index,light->brightness);
          }
          index++;
          if (light->brightnessDirection!=EEPROM.read(index)) {
            // should write
            if (EEPROM.read(base)==55) {
              // Indicate data is invalid/inconsistent (lightOn, brightness, brihtnessDirection)
              EEPROM.write(base,73);
            }
            // save the value
            EEPROM.write(index,light->brightnessDirection);
          }
          index++;
          // Validate the values
          EEPROM.write(base,55);
          // Turn off the on-board led
          //pinMode(1,INPUT);
          cbi(DDRB,1);
        } // if x ms in idle state
        break;
      case 1:
        // button released in first time of button pressed, toggle on/off
        if (light->lightOn==0) {
          light->lightOn=1; // was off, toggle to on
        } else {
          light->lightOn=0; // was not off, toggle to off
        }
        break;
    }
    // Button not pressed, goto state 0
    light->state=0;
  }
  // set th pwm value accordingly
  myAnalogWrite(light);
  
  
  int testMode=0; // debug
  switch (testMode) {
    case 1:
      //pinMode(1,INPUT);
      cbi(TCCR1,PWM1A); // pwm off
      if (button->outValue==LOW) {
        sbi(PORTB,1);
      } else {
        cbi(PORTB,1);
      //light->brightness=0;
      //digitalWrite(light->pin,LOW);
    }
    //digitalWrite(1,LOW);
    //analogWrite(light->pin,light->brightness);
    break;
    case 2:
      // digital read
      break;
  } // einde debug switch
  
  if (light->previousState!=light->state) {
    // State has changed
    light->cyclesInThisState=0; // reset counter
  } else {
    if (light->cyclesInThisState<10000000L) {
      // increment
      light->cyclesInThisState++;
    }
  }
  light->previousState=light->state;
}
void loopButton(void *b) {
  Button *button;
  button=(Button *)b;
  int actualValue= (PINB & (1 << button->pin))?HIGH:LOW;
  // Change?
  if (actualValue==button->lastValue) {
    // Is same as last, so it is stable
    if (button->stableCycles<250) button->stableCycles++; // avoid overflow
    if (button->stableCycles>2) {
      // expose the new value
      if (actualValue!=button->outValue) {
        // This is really a change in value
        button->outValue=actualValue;
        button->timePressed=0;
      }
    }
  } else {
    // actual value is different from lastValue
    button->stableCycles=0;
  }
  button->lastValue=actualValue;
  button->timePressed++; // count the number of loops the button was pressed
}
void loop() {
  int t1;
  
  loopButton(&button1);
  loopLight(&light1,&button1);
  loopButton(&button2);
  //light2.brightness=150;
  
  int analogValue=0;
  int value1;
  int debugMode=0;
  switch (debugMode) {
  case 1:
    // analog read pb4, vcc as ref, left justified, pb4 is single ended input
    ADMUX=0b00100010;
    // Start: ADEN=1, START CONVERSION, no auto trigger, no interr.flag, no interr.enable, prescaler 100=32
    ADCSRA=0b11000100;
    // wait for ad conversion
    while (ADCSRA & (1<<ADSC)) ;
    analogValue=ADCH; // left justified 8 bit value
    if (analogValue<30) {
      button2.lastValue=LOW;
    } else {
      button2.lastValue=HIGH;
    }
    /*
    light2.brightness=analogValue;
    light2.lightOn=1;
    myAnalogWrite(light2);
    */
    
    /*
    // Disable analog
    ADCSRA=0;
    // do not disable adc2d
    //cbi(DIDR0,ADC2D);
    DIDR0=0; //
   */ 
    if (button2.lastValue==LOW) {
      //sbi(PORTB,3);
      OCR1B=0;
      //sbi(PINB,3); //toggle value
    } else {
      // button HIGH, not pressed
      OCR1B=100; // lower values give more light
      //cbi(PORTB,3);
    } // if button2->outValue==LOW
    break;
  case 2:
    // digital read pb4
    ADCSRA=0; // disable A/D converter
    DIDR0=0; // enable digital input
    cbi(DDRB,4); //input pin
    sbi(PORTB,4); // pull-up resistor on/off
    value1=PINB&(1<<4);
     if (value1!=0) {
      // high, button not pressed
      OCR1B=18; // lower values more light
    } else {
      // low, button is pressed
      OCR1B=256-12;
    }
    break;
  default:
    loopLight(&light2,&button2);
  } // end of switch(debugMode
  
  delay(LOOPTIME);
}

