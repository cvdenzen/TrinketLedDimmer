#include <EEPROM.h>
#include "leddimmerwithpushbutton.h"
/*

led dimmer with push button control, using aTTiny85

Circuit:

GPIO#4: output PWM light 1,
B4, OC1B output PWM. This pin is used for USB programming.
Disadavantage of double use of this output pwm (OCR0B): leds will flicker
during programming.

GPIO#3: not used externally,
PB3, OC1B(inv), output PWM?. This pin is used for USB programming.

GPIO#2: input button for light 1,
PB2, input switch 1.

GPIO#1: output PWM light 2,
PB1 OC1A output PWM (Pulse Width Modulation),
connected to onboard led, (like pin 13 on a regular Arduino)

GPIO#0: input button for light 2,
PB0 OC1A(inv) output PWM.

Input buttons are connected to GND and with a resistor (10k) and a capacitor (10nF)
to the input pins.

Output PWM are connected to N-channel HEXFET, so high output will light the leds.

*/

#define button1Pin 2
#define button2Pin 0
#define led1Pin 4
#define led2Pin 1 /* also onboard led */

// If the button is pressed shorter than onOffButtonTime, the
// on/off status of the led is toggled. Unit is 10ms.
#define onOffButtonTime 100 /* in units of 10ms */

// The time (number of loops, unit is 10ms) it takes to increment/decrement brightness.
#define timePerStep1 2
// The number of loops when the increment/decrement brightness is adjusted 
#define stepsSpeed1 100
#define timePerStep2 1



Light light1={4,0,0,0,0,0,0L,0};
Light light2={1,10,0,0,0,0,0L,0};
Button button1={button1Pin,HIGH,HIGH,0,0};
Button button2={button2Pin,HIGH,HIGH,0,0};

// Stupid Arduino IDE makes me use a void pointer as intermediate.
// See: http://forum.arduino.cc/index.php/topic,41848.0.html
void setupButton(void *b) {
  Button *button;
  button=(Button *)b;
  // pull up resistor enable for button inputs PB0 and PB2
  pinMode(button->buttonPin,INPUT);
  digitalWrite(button->buttonPin,HIGH);
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
}

void setup() {
  setupButton(&button1);
  setupButton(&button2);
  // set output pins to output
  pinMode(led1Pin,OUTPUT);
  pinMode(led2Pin,OUTPUT);

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
    switch (light->state) {
      case 0:
        // do nothing
        light->state=1; // button pressed
        break;
      case 1:
        // if time-out, then goto state 2
        if (button->timePressed>onOffButtonTime) {
          // end of state 1
          light->state=2;
        }
        break;
      case 2:
        // put light on
        light->lightOn=1;
        if (light->brightnessDirection==0) {
          // 0 is illegal value
          light->brightnessDirection=1;
        }
        if ((light->brightness>=255) && (light->brightnessDirection>0)) {
          // oops, would cause overflow, so change direction
          light->brightnessDirection=-1;
        }
        if ((light->brightness<=5) && (light->brightnessDirection<0)) {
          // oops, would cause overflow, so change direction
          light->brightnessDirection=1;
        }
        // every timePerStep1 loops, adjust the brightness
        int timePerStep=timePerStep1; // default during first time period
        if (button->timePressed>stepsSpeed1) {
          timePerStep=timePerStep2;
        }
        // Method 2: if brightness is high, then accelerate faster
        int stepsPerCycle=(light->brightness / 20)+1;
        timePerStep=20 - (light->brightness / 100);
        if (timePerStep<1) {
          timePerStep=1;
        }
        timePerStep=1;
        if ((button->timePressed % timePerStep) == 0 ) {
          light->brightness+=light->brightnessDirection;
        }
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
        }
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
    light->state=0;
  }
  // set th pwm value accordingly
  analogWrite(light->pin,(light->lightOn>0)?light->brightness:0);
  //analogWrite(light->pin,light->brightness);
  
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
  int actualValue=digitalRead(button->buttonPin);
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
  loopLight(&light2,&button2);

  //analogWrite(1,200); // debug

  //delay(100);

  //analogWrite(1,12); // debug
  /*
  t1=digitalRead(button1Pin);
  if (t1==LOW) {
    analogWrite(1,200);
  }
  */
  
  /*
  //t1=digitalRead(button2Pin);
  if (button2.outValue==LOW) {
    analogWrite(1,5);
  }
  */
  delay(10);
}

