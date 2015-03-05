#include <AnalogDemux.h>

#define maxMuxOutput 8
#define varyingPin 3

byte selectPins[] = {4, 5, 6};

AnalogDemux demux(maxMuxOutput, varyingPin, selectPins);

byte outputIndex, analogValue;

void setup(){
  demux.init();
}

void loop(){
  outputIndex = 5; 
  analogValue = 255;

  demux.writeAtIndex(outputIndex, analogValue);
}