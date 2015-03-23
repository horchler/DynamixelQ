/*
 *	tosser.ino
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 3-22-15, modified: 3-22-15
 */

#include "DynamixelQ.h"
#include "DXL_Utils.h"
#include "USBprint.h"

// Instantiate DynamixelQ object for MX-64 actuators
DynamixelQ Dxl(DXL_MX64);

void blinkOnce(void)
{
  digitalWrite(BOARD_LED_PIN, LOW);
  delay_us(100);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

void setup()
{
  byte return_delay = 0;
  
  // Start communicating with actuators at 3 Mbps
  Dxl.begin(DXL_BAUD_3000000);
  delay(3000);
  USBprint("\nInitializing... ");
  
  // Stop all actuators in case any are moving
  Dxl.zeroSpeed();
  delay(1000);
  
  // Set DXL_RETURN_DELAY_TIME to 0 ms on all actuators
  Dxl.setReturnDelay(return_delay);
  
  pinMode(BOARD_LED_PIN, OUTPUT);
  blinkOnce();
  delay(1000);
  USBprint("Initialized.\n");
}

void loop()
{
  uint8 USBdata, DXLdata;
  
  if (usbBytesAvailable()) {
    USBdata = SerialUSB.read();
    blinkOnce();
    Dxl.writeRaw(USBdata);
  }
  
  if (Dxl.available()) {
    DXLdata = Dxl.readRaw();
    blinkOnce();
    USBprintRaw(DXLdata);
  }  
}