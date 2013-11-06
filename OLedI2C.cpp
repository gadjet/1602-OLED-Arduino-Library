/*
This is my first Library to make writing to the OLED 1602
Display much easier, the display is based on the SSD1311.
The display has 16 characters and 2 lines.
The library is far from complete and may be prone to errors.
Feedback welcome, visit www.gadjet.co.uk
Phil Grant 2013
Scrolling contributed by Nathan Chantrell http://nathan.chantrell.net/

Updated 06/11/2013 to include the cursPos data in the sendString function
sendString("string", col, row)

*/
#include "OLedI2C.h" 
#include "Wire.h"
#define OLED_Address 0x3c
#define OLED_Command_Mode 0x80
#define OLED_Data_Mode 0x40

OLedI2C::OLedI2C(){}
OLedI2C::~OLedI2C(){}


void OLedI2C::init() {
   // *** I2C initial *** //
 delay(100);
 sendCommand(0x2A);	// **** Set "RE"=1	00101010B
 sendCommand(0x71);
 sendCommand(0x5C);
 sendCommand(0x28);

 sendCommand(0x08);	// **** Set Sleep Mode On
 sendCommand(0x2A);	// **** Set "RE"=1	00101010B
 sendCommand(0x79);	// **** Set "SD"=1	01111001B

 sendCommand(0xD5);
 sendCommand(0x70);
 sendCommand(0x78);	// **** Set "SD"=0  01111000B

 sendCommand(0x08);	// **** Set 5-dot, 3 or 4 line(0x09), 1 or 2 line(0x08)

 sendCommand(0x06);	// **** Set Com31-->Com0  Seg0-->Seg99

 // **** Set OLED Characterization *** //
 sendCommand(0x2A);  	// **** Set "RE"=1 
 sendCommand(0x79);  	// **** Set "SD"=1

 // **** CGROM/CGRAM Management *** //
 sendCommand(0x72);  	// **** Set ROM
 sendCommand(0x00);  	// **** Set ROM A and 8 CGRAM


 sendCommand(0xDA); 	// **** Set Seg Pins HW Config
 sendCommand(0x10);   

 sendCommand(0x81);  	// **** Set Contrast
 sendCommand(0xFF); 

 sendCommand(0xDB);  	// **** Set VCOM deselect level
 sendCommand(0x30);  	// **** VCC x 0.83

 sendCommand(0xDC);  	// **** Set gpio - turn EN for 15V generator on.
 sendCommand(0x03);

 sendCommand(0x78);  	// **** Exiting Set OLED Characterization
 sendCommand(0x28); 
 sendCommand(0x2A); 
 //sendCommand(0x05); 	// **** Set Entry Mode
 sendCommand(0x06); 	// **** Set Entry Mode
 sendCommand(0x08);  
 sendCommand(0x28); 	// **** Set "IS"=0 , "RE" =0 //28
 sendCommand(0x01); 
 sendCommand(0x80); 	// **** Set DDRAM Address to 0x80 (line 1 start)

 delay(100);
 sendCommand(0x0C);  	// **** Turn on Display
 }
 
 void OLedI2C::cursPos(uint8_t col, uint8_t row)
 {
 int row_offsets[] = { 0x00, 0x40 };
 sendCommand(0x80 | (col + row_offsets[row]));
 }
 
void OLedI2C::clearLcd()
{
sendCommand(0x01);
}

 void OLedI2C::sendCommand(unsigned char command)
{
    Wire.beginTransmission(OLED_Address); 	 // **** Start I2C 
    Wire.write(OLED_Command_Mode);     		 // **** Set OLED Command mode
    Wire.write(command);
    Wire.endTransmission();                 	 // **** End I2C 
      delay(10);
}
void OLedI2C::sendString(const char *String, uint8_t col, uint8_t row)
{
  cursPos(col, row);
  unsigned char i=0;
  while(String[i])
  {
    sendData(String[i]);      // *** Show String to OLED
    i++;
  }
}
void OLedI2C::sendData(unsigned char data)
{
  Wire.beginTransmission(OLED_Address);  	// **** Start I2C 
  Wire.write(OLED_Data_Mode);     		// **** Set OLED Data mode
  Wire.write(data);
  Wire.endTransmission();                     // **** End I2C 
}
void OLedI2C::scrollString(char* message, byte row, unsigned int time)//written by Nathan Chantrell http://nathan.chantrell.net/
{ 
 char buffer[16];
 for (byte i=0;i<strlen(message)+16;i++) {
  byte pos = i+1;
  for (byte j=0;j<16;j++) {
   if ((pos<16)||(pos>strlen(message)+15)) { // pad and trail with blank spaces
     buffer[j]=' ';
   }
   else buffer[j]=message[pos-16];
   pos++;
  }
 //cursPos(0,row); removed by PG
 sendString(buffer, 0, row); //Edited by PG tho include the cursor pos within the sendString command
 delay(time);
 }
}
