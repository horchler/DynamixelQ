/*
 *	DXL_Address.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 10-3-14
 */

#ifndef DXL_Address_H_
#define DXL_Address_H_

#include "DXL_AX.h"
#include "DXL_MX.h"

// Dynamixel register addresses common to all servos
#define DXL_MODEL_NUMBER 0
#define DXL_VERSION_OF_FIRMWARE 2
#define DXL_ID 3
#define DXL_BAUD_RATE 4
#define DXL_RETURN_DELAY_TIME 5
#define DXL_CW_ANGLE_LIMIT 6
#define DXL_CCW_ANGLE_LIMIT 8
#define DXL_THE_HIGHEST_LIMT_TEMPERATURE 11
#define DXL_THE_LOWEST_LIMT_VOLTAGE 12
#define DXL_THE_HIGHEST_LIMT_VOLTAGE 13
#define DXL_MAX_TORQUE 14
#define DXL_STATUS_RETURN_LEVEL 16
#define DXL_ALARM_LED 17
#define DXL_ALARM_SHUTDOWN 18

#define DXL_TORQUE_ENABLE 24
#define DXL_LED 25

#define DXL_GOAL_POSITION 30
#define DXL_MOVING_SPEED 32
#define DXL_TORQUE_LIMIT 34
#define DXL_PRESENT_POSITION 36
#define DXL_PRESENT_SPEED 38
#define DXL_PRESENT_LOAD 40
#define DXL_PRESENT_VOLTAGE 42
#define DXL_PRESENT_TEMPERATURE 43
#define DXL_REGISTERED 44
#define DXL_MOVING 46
#define DXL_LOCK 47
#define DXL_PUNCH 48

#define DXL_BYTE 0
#define DXL_WORD_L 1
#define DXL_WORD_H 2
#define DXL_UNDEFINED 3
#define DXL_NUM_ADDRESS 74

static byte DXL_ADDRESS_TYPE[DXL_NUM_ADDRESS] = {1,2,0,0,0,0,1,2,1,2,3,0,0,0,1,2,0,0,0,3,
							   					 1,2,0,3,
							   					 0,0,
							   					 0,0,0,3,
							   					 1,2,1,2,1,2,1,2,1,2,1,2,0,0,0,3,0,0,1,2,
							   					 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
							   					 1,2,0,1,2,
							   					 0};

#endif /* DXL_Address_H_ */