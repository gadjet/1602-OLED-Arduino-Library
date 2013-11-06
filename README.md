1602-OLED-Arduino-Library
=========================

wide.HK 1602 OLED Library

This Library is intended for the Wide.HK OLED 1602 display.

KEYWORDS

OLedI2C		    KEYWORD1

init		      KEYWORD2

sendCommand	  KEYWORD2

sendString	  KEYWORD2

sendData	    KEYWORD2

clearLcd	    KEYWORD2

cursPos		    KEYWORD2

scrollString	KEYWORD2 Writen by Nathan Chantrell http://nathan.chantrell.net

Updated sendString to include cursPos data. sendString("String", col, row)
Updated Library by adding sendFloat function, this allows a float value to be
sent to the LCD, the float is converted to a string and sent using the sendString function
