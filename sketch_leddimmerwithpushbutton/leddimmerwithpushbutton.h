#include <stdio.h>

#define byte uint8_t
typedef struct {
  byte pin;
  int eepromOffset;
  byte lightOn; // whether this led is on of off
  byte brightness;
  // state:
  // 0=initial
  // 1=
  byte state; // state of the control
  int8_t brightnessDirection; // 1=going up, -1=going down in brightness
  byte previousBrightness; // previous value
  unsigned long cyclesInThisState; // the number of cycles we are in this state
  byte previousState;
} Light;

// A button with debounce data
typedef struct {
  int pin;
  byte outValue; // the value that is exposed to the client
  byte lastValue; // the value during the previous loop
  byte stableCycles; // the number op loops the lastValue was stable
  unsigned long timePressed; // in units of 10 ms
} Button;


