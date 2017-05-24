#include <MIDI.h>
#define MIDI_ENABLE 12

// Variables:
int cc = 0;
int AnalogValue = 0; // define variables for the controller data
int lastAnalogValue = 0; // define the "lastValue" variables

void setup() {
  
   
  //  launch MIDI
  MIDI.begin(4)
}

void loop() {
  AnalogValue = analogRead(0);
  //  convert to a range from 0 to 127:
  cc = AnalogValue/8;
  // check if analog input has changed
  if (lastAnalogValue != cc) {
    MIDI.sendControlChange(16,cc,1);
    // update lastAnalogValue variable
    lastAnalogValue = cc;
  
AnalogValue = analogRead(1);
  //  convert to a range from 0 to 127:
  cc = AnalogValue/8;
  // check if analog input has changed
  if (lastAnalogValue != cc) {
    MIDI.sendControlChange(17,cc,1);
    // update lastAnalogValue variable
    lastAnalogValue = cc;
  }   //  endif

AnalogValue = analogRead(2);
  //  convert to a range from 0 to 127:
  cc = AnalogValue/8;
  // check if analog input has changed
  if (lastAnalogValue != cc) {
    MIDI.sendControlChange(18,cc,1);
    // update lastAnalogValue variable
    lastAnalogValue = cc;
  }   //  endif
  
}
