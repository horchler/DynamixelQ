/*
 *	three_servos.ino
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-24-14, modified: 10-4-14
 */

#define DXL_MX64

#include "DynamixelQ.h"
#include "USBprint.h"

DynamixelQ Dxl(DXL_MX64);

#define NUM_SERVOS 3

static byte servo_ids[NUM_SERVOS] = {
	1,2,3
};

inline double movingAverge(double Yt)
{
	static int n = 0;
	static double St = 0.0;

	St += Yt;
	return St/(++n);
}

void setup() {
	word init_angle_limits[2] = {0,0}, init_speeds[NUM_SERVOS] = {100,200,300};

	// Start communicating with dynamixels at 3 Mbps
	Dxl.begin(DXL_BAUD_3000000);
	delay(3000);

	// Stop all actuators in case they are moving
	Dxl.writeWord(BROADCAST_ID, DXL_TORQUE_LIMIT, (word)0);
	Dxl.writeWord(BROADCAST_ID, DXL_MOVING_SPEED, (word)0);

	// Set return delay to 0 ms on three actuators
	Dxl.writeByte(servo_ids, NUM_SERVOS, DXL_RETURN_DELAY_TIME, (byte)0);

	// Set angle DXL_CW_ANGLE_LIMIT and DXL_CCW_ANGLE_LIMIT on to specify wheel mode
	Dxl.syncWrite(servo_ids, NUM_SERVOS, DXL_CW_ANGLE_LIMIT, init_angle_limits, 2, 2);
	delay(1000);

	// Set speed of three actuators to different values
	Dxl.writeWord(servo_ids, NUM_SERVOS, DXL_TORQUE_LIMIT, (word)1023);
	Dxl.writeWord(servo_ids, NUM_SERVOS, DXL_MOVING_SPEED, init_speeds);
	delay(1000);
}

void loop() {
	const byte NUM_ADDRESSES = 3;
	int i;
	static unsigned long iter = 0;
	unsigned long tstart, ttime;
	double meantime;
	word positionSpeedLoadData[NUM_SERVOS*NUM_ADDRESSES];

	delay_us(100);	// Minimum loop delay

	tstart = micros();

	// Read present position and load (non-adjacent addresses) from all actuators and store in array
	Dxl.syncRead(servo_ids, NUM_SERVOS, DXL_PRESENT_POSITION, NUM_ADDRESSES, positionSpeedLoadData);

	// Timing statistics
	ttime = micros()-tstart;
	meantime = movingAverge(ttime);
	iter++;

	if (iter%10 == 0) {
		// Print timing statistics with labels all at once, every 10 iterations
		USBprint("Iteration %u - Time: %u, Mean: %.8f\n",iter,ttime,meantime);

		// Print position, speed, and load integer data for each actuator, every 
		for (i = 0; i < NUM_SERVOS; i++) {
			USBprintInt("   Servo %u - Position: %u, Speed: %u, Load: %u\n",
						servo_ids[i], positionSpeedLoadData[NUM_ADDRESSES*i],
									  positionSpeedLoadData[NUM_ADDRESSES*i+1],
									  positionSpeedLoadData[NUM_ADDRESSES*i+2]);
		}
	}
}