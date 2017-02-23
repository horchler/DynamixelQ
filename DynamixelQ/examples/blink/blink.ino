/*
 *	blink.ino
 *	
 *	Demonstrate timer-based asynchronous blink functions.
 *	
 *	Author: Andrew D. Horchler, horchler @ gmail . com
 *	Created: 4-22-15, modified: 4-22-15
 */

#include "DynamixelQ.h"
#include "USBprint.h"

void setup()
{
  delay(1000);
  USBprint("Initializing... ");
  delay(1000);
  
  // Single one-second blink
  Board.blinkOnce(1e6);
  delay(2000);
  
  USBprint("Initialized.\n");
  
  // Blink continuously with 0.1-second period (0.05-second blinks)
  Board.blink(1e5);
}

void loop()
{
  // Print continuously while blinking
  USBprint("Elapsed time: %u milliseconds.\n", millis());
  delay(1000);
}