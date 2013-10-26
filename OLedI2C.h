/*
	OLedI2C.h
	OLED 1602 Library for the I2C
	OLED display from WIDE.HK
	Also my first attempt at a Library
	Phil Grant Sept 2013
	www.gadjet.co.uk
	Scrolling contributed by Nathan Chantrell http://nathan.chantrell.net/
*/
#ifndef OLedI2C_h
#define OLedI2C_h	
#include "Arduino.h"
#include "Wire.h"

class OLedI2C {
public:
		OLedI2C();
		~OLedI2C();
		void init();
		void sendCommand(unsigned char command);
		void sendString(const char *String);
		void sendData(unsigned char data);
		void clearLcd();
		void cursPos(uint8_t, uint8_t); // cloumn, row
		void scrollString(char* message, byte row, unsigned int time); //written by Nathan Chantrell http://nathan.chantrell.net/
};
#endif
