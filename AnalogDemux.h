#ifndef AnalogDemux_h
#define AnalogDemux_h

#include "Arduino.h"

class AnalogDemux
{
	public:
		AnalogDemux(byte maxOutput, byte varyingPin, byte* selectPins);
		void init();
		void selectOutputAtIndex(byte index);
		void write(byte value);
		void writeAtIndex(byte index, byte value);
	private:
		byte _maxOutput;
		byte _varyingPin;
		byte *_selectPins;
		byte _numberOfSelectPins;

		byte _getNumberOfBitNeededForAGivenNumber(byte givenNumber);
};

#endif