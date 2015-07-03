/*
 *	tosser.ino
 *	
 *	Simple tosser. Read available bytes individually from USB serial port and write them
 *	directly to Dynamixel serial bus. Read available bytes individually from Dynamixel
 *	serial bus and write them directly to the USB serial port.
 *	
 *	Actuators must be MX Series actuators. Change the baud rate to DXL_BAUD_1000000 or
 *	less to handle AX Series actuators or mixed types.
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 3-22-15, modified: 7-3-15
 */

#include "DynamixelQ.h"
#include "USBprint.h"

void setup()
{
  // Start communicating with actuators at 3 Mbps
  Dxl.begin(DXL_BAUD_3000000);
  delay(100);
  
  Board.blinkOnce(1e6);
}

void loop()
{
  uint8 USBdata, DXLdata;
  
  // Read raw byte from USB serial connction and write to Dynamixel bus
  if (usbBytesAvailable()) {
    USBdata = SerialUSB.read();
    Board.blinkOnce(100);
    delay_us(100);
    Dxl.writeRaw(USBdata);
  }
  
  // Read raw byte from Dynamixel bus and write to USB serial connection
  if (Dxl.available()) {
    DXLdata = Dxl.readRaw();
    Board.blinkOnce(100);
    delay_us(100);
    USBprintRaw(DXLdata);
  }  
}