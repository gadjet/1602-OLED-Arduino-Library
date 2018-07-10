/*
Example sketch to display Strings and float values on the OLED
1602 display  from Wide.HK. This uses a Lbrary that I've
put together containing some basic functions.
The I2C Address is set to 0x3C in OLedI2C.cpp
Phil Grant 2013 www.gadjet.co.uk  07/11/13
*/

#include "Wire.h"
#include "OLedI2C.h"
OLedI2C LCD;
float digit; //Variable to hold sample temperature value

void setup()
{
  Wire.begin();
  LCD.init();
  digit = 21.6; //This would normally be the float value returned from a temp sensor or other sensor
}
void loop()
{
  LCD.sendString("Temp",0,0);  //Now includes the cursor position data (col, row)
  LCD.sendFloat(digit,5,2,7,0);  //Send the float value to the display starting 
                                //at col 7 row 1 with 5 digits and 2 decimal places
  while(1);
}
