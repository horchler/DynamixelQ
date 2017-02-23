/*
 *	fade.ino
 *	
 *	Demonstrate timer-based asynchronous fade functions.
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
  
  // Single two-second fade to maximum brightness
  Board.fadeOnce(BOARD_LED_MAX_BRIGHTNESS, 2e6);
  delay(3000);
  
  USBprint("Initialized.\n");
  
  // Fade continuously with one-second period (0.5-second fades)
  Board.fade(0x7FFF, 1e6);
}

void loop()
{
  // Print continuously while fading
  USBprint("Elapsed time: %u milliseconds.\n", millis());
  delay(1000);
}