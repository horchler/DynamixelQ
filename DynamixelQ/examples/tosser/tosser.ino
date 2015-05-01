/*
 *	tosser.ino
 *	
 *	Simple tosser. Read available bytes from USB serial port and write them directly to
 *	Dynamixel serial bus. Read available bytes from Dynamixel serial bus and write them
 *	directly to the USB serial port. Note that USBprint is used to print character strings
 *	to the USB serial port during initialization.
 *	
 *	Actuators must be MX Series actuators. Change the baud rate to DXL_BAUD_1000000 or
 *	less to handle AX Series actuators or mixed types.
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 3-22-15, modified: 4-30-15
 */

#include "DynamixelQ.h"
#include "USBprint.h"

void setup()
{
  byte return_delay = 0;
  
  // Start communicating with actuators at 3 Mbps
  Dxl.begin(DXL_BAUD_3000000);
  delay(1000);
  USBprint("\nInitializing... ");
  
  // Stop all actuators in case any are moving
  Dxl.stop();
  delay(1000);
  
  // Set DXL_RETURN_DELAY_TIME to 0 ms on all actuators
  Dxl.setReturnDelay(return_delay);
  
  Board.blinkOnce(1e6);
  delay(1000);
  USBprint("Initialized.\n");
}

void loop()
{
  uint8 USBdata, DXLdata;
  
  if (usbBytesAvailable()) {
    USBdata = SerialUSB.read();
    Board.blinkOnce(100);
    delay_us(100);
    Dxl.writeRaw(USBdata);
  }
  
  if (Dxl.available()) {
    DXLdata = Dxl.readRaw();
    Board.blinkOnce(100);
    delay_us(100);
    USBprintRaw(DXLdata);
  }  
}