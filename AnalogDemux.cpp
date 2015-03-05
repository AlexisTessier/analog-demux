#include "Arduino.h"
#include "AnalogDemux.h"

AnalogDemux::AnalogDemux(byte maxOutput, byte varyingPin, byte* selectPins){
	_maxOutput = maxOutput;
	_varyingPin = varyingPin;
	_selectPins = selectPins;

	_numberOfSelectPins = _getNumberOfBitNeededForAGivenNumber(_maxOutput-1);
}

void AnalogDemux::init(){
	byte i, imax;
	
	pinMode(_varyingPin, OUTPUT);
	analogWrite(_varyingPin, 0);
	
	imax = _numberOfSelectPins;
	for(i=0;i<imax;i++){
		pinMode(_selectPins[i], OUTPUT);
		digitalWrite(_selectPins[i], 0);
	}
}

byte AnalogDemux::_getNumberOfBitNeededForAGivenNumber(byte givenNumber){
	byte currentMaxValue, currentExponent;
	int powValue;

	currentExponent = 0;
	powValue = 2;
	currentMaxValue = 1;
	while(currentExponent < 255 && currentMaxValue < givenNumber){
		currentExponent++;
		currentMaxValue += powValue;
		powValue *= 2;
	}

	return currentExponent+1;
}

void AnalogDemux::selectOutputAtIndex(byte index){
	int i, imax, bitwiseLeft, bitwiseRight, bitwiseResult;

	imax = _numberOfSelectPins;
	bitwiseRight = 1;
	bitwiseLeft = (int)index;

	for(i=0;i<imax;i++){
		bitwiseResult = bitwiseLeft & bitwiseRight;
		
		digitalWrite(_selectPins[i], bitwiseResult > 0 ? HIGH : LOW);
		bitwiseRight *= 2;
	}
}

void AnalogDemux::write(byte value){
	analogWrite(_varyingPin, value);
}

void AnalogDemux::writeAtIndex(byte index, byte value){
	write(0);
	selectOutputAtIndex(index);
	write(value);
}

