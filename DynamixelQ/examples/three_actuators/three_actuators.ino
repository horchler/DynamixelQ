/*
 *	three_actuators.ino
 *	
 *	Run Actuator IDs 1, 2, and 3 at three different constant speeds in wheel mode. Read
 *	position, speed, and load from each. Use USBprint to print read data and timing
 *	statistics to the USB serial port.
 *	
 *	Actuator IDs 1, 2, and 3 must be MX Series actuators. Change the baud rate to
 *	DXL_BAUD_1000000 or less to handle AX Series actuators or mixed types.
 *	
 *	Author: Andrew D. Horchler, horchler @ gmail . com
 *	Created: 8-24-14, modified: 4-30-15
 */

#include "DynamixelQ.h"
#include "USBprint.h"

// Specify IDs of Dynamixels
#define NUM_ACTUATORS 3
static byte actuator_ids[NUM_ACTUATORS] = {
	1,2,3
};

// Elapsed time in microsceonds 
unsigned long usElapsed(void)
{
  unsigned long t_prv;
  static unsigned long t_now = 0;
  static int isInit = 1;
  
  if (isInit) {
    isInit = 0;
    t_now = micros();
    
    return 0;
  } else {
    t_prv = t_now;
    t_now = micros();
    
    return t_now - t_prv;
  }
}

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
  byte i, return_delay = 0;
  word init_speeds[NUM_ACTUATORS] = {100,200,300};
  
  // Start communicating with actuators at 3 Mbps
  Dxl.begin(DXL_BAUD_3000000);
  delay(1000);
  USBprintf("\nInitializing... ");
  
  // Stop all actuators in case any are moving
  Dxl.stop();
  delay(1000);
  
  // Check if specified actuator_ids exist and are communicating
  for (i = 0; i < NUM_ACTUATORS; i++) {
    while (!Dxl.isID(actuator_ids[i])) {
      USBprintf("Actuator ID %u not found. Looking...\n", actuator_ids[i]);
      delay(2000);
    }
    USBprintf("Actuator ID %u found... ", actuator_ids[i]);
  }

  // Set DXL_RETURN_DELAY_TIME to 0 ms on actuator_ids
  Dxl.setReturnDelay(actuator_ids, NUM_ACTUATORS, return_delay);
  
  // Set DXL_CW_ANGLE_LIMIT, DXL_CCW_ANGLE_LIMIT, and DXL_TORQUE_LIMIT on actuator_ids to specify wheel mode
  Dxl.setWheelMode(actuator_ids, NUM_ACTUATORS);
  
  // Initialize DXL_MOVING_SPEED on actuator_ids
  Dxl.setSpeed(actuator_ids, NUM_ACTUATORS, init_speeds);
  USBprintf("Initialized.\n");
  delay(1000);
}

void loop()
{
  static unsigned long iter = 0;
  unsigned long read_duration, print_duration;
  double mean_total_duration;
  byte i, start_addr = DXL_PRESENT_POSITION, num_addr = 3;
  word position_speed_load_data[num_addr*NUM_ACTUATORS];
  
  // Elapsed time for printing and reset timer
  print_duration = usElapsed();
  
  // Read present position, speed, and load from all actuators in actuator_ids and store in array
  Dxl.syncRead(actuator_ids, NUM_ACTUATORS, start_addr, num_addr, position_speed_load_data);
  
  // Elapsed time for reading and reset timer
  read_duration = usElapsed();
  mean_total_duration = movingAverge(read_duration+print_duration);
  iter++;
  
  // Print timing statistics
  USBprintf("Iteration %u - Read duration: %u us, Print duration: %u, Mean total duration: %.4f us\n",
    iter,read_duration,print_duration,mean_total_duration);
  // Print position, speed, and load data for each actuator in actuator_ids 
  for (i = 0; i < NUM_ACTUATORS; i++) {
    USBprintf("  -  Actuator: %u  -  Position: %u, Speed: %u, Load: %u\n",
      actuator_ids[i],position_speed_load_data[num_addr*i],position_speed_load_data[num_addr*i+1],position_speed_load_data[num_addr*i+2]);
  }
}