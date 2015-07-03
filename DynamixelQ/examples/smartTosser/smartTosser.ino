/*
 *	smartTosser.ino
 *	
 *	Smart tosser. Read all available bytes from USB serial port and write them directly
 *	to Dynamixel serial bus. Read all available bytes from Dynamixel serial bus and write
 *	them directly to the USB serial port.
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
  
  // Enable timer-based asynchronous blinking
  Board.blink(1e4);
}

void loop()
{
  const uint16 wSize = 256;
  uint8 bNum, bData[wSize];
  
  // Read all available raw bytes from USB serial connction and write to Dynamixel bus
  bNum = usbBytesAvailable();
  SerialUSB.read(bData, bNum);
  Dxl.writeRaw(bData, bNum);
  
  // Read all available raw bytes from Dynamixel bus and write to USB serial connection
  bNum = Dxl.readRaw(bData, wSize);
  _USBprintRaw(bData, bNum);
}