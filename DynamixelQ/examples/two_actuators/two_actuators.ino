/*
 *	two_actuators.ino
 *	
 *	Run Actuator IDs 1 and 2 at different speeds in joint mode. Read position and speed
 *	from each. Use USBprint to print read data and timing statistics to the USB serial
 *	port.
 *	
 *	Actuator IDs 1 and 2 must be MX Series actuators. Change the baud rate to
 *	DXL_BAUD_1000000 or less to handle AX Series actuators or mixed types.
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 7-28-15, modified: 7-28-15
 */

#include "DynamixelQ.h"
#include "USBprint.h"

// Specify IDs of Dynamixels
#define NUM_ACTUATORS 2
static byte actuator_ids[NUM_ACTUATORS] = {
	1,2
};

word initial_position[NUM_ACTUATORS];
unsigned long t0;

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
  
  // Set DXL_CW_ANGLE_LIMIT, DXL_CCW_ANGLE_LIMIT, and DXL_TORQUE_LIMIT on actuator_ids to specify joint mode
  Dxl.setJointMode(actuator_ids, NUM_ACTUATORS);
  
  // Zero position of actuator_ids to their current positions
  Dxl.zero(actuator_ids, NUM_ACTUATORS, initial_position);
  
  USBprintf("Initialized.\n");
  delay(1000);
  
  // Phase offest for sinusoidal oscillations
  t0 = millis();
}

void loop()
{
  static unsigned long iter = 0;
  unsigned long read_duration, print_duration;
  double mean_total_duration;
  byte i, write_start_addr = DXL_GOAL_POSITION, read_start_addr = DXL_PRESENT_POSITION;
  const byte num_addr = 2, num_data = num_addr*NUM_ACTUATORS;
  word write_position_speed_data[num_data] = {initial_position[0],160,initial_position[1],10}, read_position_speed_data[num_data];
  float delta;
  
  // Elapsed time for printing and reset timer
  print_duration = usElapsed();
  
  // Oscillate goal positions sinusoidally
  delta = 500.0*sin(0.001*float(millis()-t0));
  write_position_speed_data[0] = float(initial_position[0])+delta;
  write_position_speed_data[2] = float(initial_position[1])+delta;
  
  // Write goal position and moving speed to all actuators in actuator_ids
  Dxl.syncWrite(actuator_ids, NUM_ACTUATORS, write_start_addr, write_position_speed_data, num_addr, num_data);
  
  // Read present position and speed from all actuators in actuator_ids and store in array
  Dxl.syncRead(actuator_ids, NUM_ACTUATORS, read_start_addr, num_addr, read_position_speed_data);
  
  // Elapsed time for reading and reset timer
  read_duration = usElapsed();
  mean_total_duration = movingAverge(read_duration+print_duration);
  iter++;
  
  // Print timing statistics
  USBprintf("Iteration %u - Read duration: %u us, Print duration: %u, Mean total duration: %.4f us\n",
    iter,read_duration,print_duration,mean_total_duration);
  // Print position and speed data for each actuator in actuator_ids 
  for (i = 0; i < NUM_ACTUATORS; i++) {
    USBprintf("  -  Actuator: %u  -  Position: %u, Speed: %u\n",
      actuator_ids[i],read_position_speed_data[num_addr*i],read_position_speed_data[num_addr*i+1]);
  }
}