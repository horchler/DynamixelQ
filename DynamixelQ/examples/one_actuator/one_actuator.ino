/*
 *	one_actuator.ino
 *	
 *	Run Actuator ID 1 at constant speed in wheel mode. Read position, speed, and load.
 *	Use USBprint to print read data and timing statistics to the USB serial port.
 *	
 *	Actuator ID 1 must be an MX Series actuator. Change the baud rate to DXL_BAUD_1000000
 *	or less to handle AX Series actuators or mixed types.
 *	
 *	Author: Andrew D. Horchler, horchler @ gmail . com
 *	Created: 8-24-14, modified: 7-28-15
 */

#include "DynamixelQ.h"
#include "USBprint.h"

// Specify ID of Dynamixel
#define ACTUATOR_ID 1

// Calculate moving average
inline double movingAverge(double Yt)
{
  static int n = 0;
  static double St = 0.0;
  
  St += Yt;
  return St/(++n);
}

void setup()
{
  byte return_delay = 0;
  word init_speed = 100;
  
  // Start communicating with actuators at 3 Mbps
  Dxl.begin(DXL_BAUD_3000000);
  delay(1000);
  USBprintf("\nInitializing... ");
  
  // Stop all actuators in case any are moving
  Dxl.stop();
  delay(1000);
  
  // Check if specified ACTUATOR_ID exists and is communicating
  while (!Dxl.isID(ACTUATOR_ID)) {
    USBprintf("Actuator ID %u not found. Looking...\n", ACTUATOR_ID);
    delay(2000);
  }
  USBprintf("Actuator ID %u found... ", ACTUATOR_ID);
  
  // Set DXL_RETURN_DELAY_TIME to 0 ms on ACTUATOR_ID
  Dxl.setReturnDelay(ACTUATOR_ID, return_delay);
  
  // Set DXL_CW_ANGLE_LIMIT, DXL_CCW_ANGLE_LIMIT, and DXL_TORQUE_LIMIT on ACTUATOR_ID to specify wheel mode
  Dxl.setWheelMode(ACTUATOR_ID);
  
  // Initialize DXL_MOVING_SPEED of ACTUATOR_ID
  Dxl.setSpeed(ACTUATOR_ID, init_speed);
  USBprintf("Initialized.\n");
  delay(1000);
}

void loop()
{
  static unsigned long iter = 0;
  unsigned long read_duration, print_duration;
  double mean_total_duration;
  byte start_addr = DXL_PRESENT_POSITION, num_addr = 3;
  word position_speed_load_data[3];
  
  // Elapsed time for printing and reset timer
  print_duration = usElapsed();
  
  // Read present position, speed, and load from ACTUATOR_ID and store in array
  // Alternative options commented out
  Dxl.syncRead(ACTUATOR_ID, start_addr, num_addr, position_speed_load_data);
  /*
  byte position_speed_load_addr[3] = {DXL_PRESENT_POSITION,DXL_PRESENT_SPEED,DXL_PRESENT_LOAD};
  position_speed_load_data[0] = Dxl.readWord(ACTUATOR_ID, position_speed_load_addr[0]);
  position_speed_load_data[1] = Dxl.readWord(ACTUATOR_ID, position_speed_load_addr[1]);
  position_speed_load_data[2] = Dxl.readWord(ACTUATOR_ID, position_speed_load_addr[2]);
  */
  /*
  position_speed_load_data[0] = Dxl.getPosition(ACTUATOR_ID);
  position_speed_load_data[1] = Dxl.getSpeed(ACTUATOR_ID);
  position_speed_load_data[2] = Dxl.getLoad(ACTUATOR_ID);
  */
  /*
  byte actuator_ids[3] = {ACTUATOR_ID,ACTUATOR_ID,ACTUATOR_ID}, num_ids = 3;
  byte position_speed_load_addr[3] = {DXL_PRESENT_POSITION,DXL_PRESENT_SPEED,DXL_PRESENT_LOAD};
  Dxl.readWord(actuator_ids, num_ids, position_speed_load_addr, position_speed_load_data);
  */
  
  // Elapsed time for reading and reset timer
  read_duration = usElapsed();
  mean_total_duration = movingAverge(read_duration+print_duration);
  iter++;

  // Print timing statistics
  USBprintf("Iteration %u - Read duration: %u us, Print duration: %u, Mean total duration: %.4f us\n  -  Position: %u, Speed: %u, Load: %u\n",
    iter,read_duration,print_duration,mean_total_duration,
    position_speed_load_data[0],position_speed_load_data[1],position_speed_load_data[2]);
}