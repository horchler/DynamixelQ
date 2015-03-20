/*
 *	DXL_Address.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 3-17-15
 */

#ifndef DXL_ADDRESS_H_
#define DXL_ADDRESS_H_

#include "DXL_AX.h"
#include "DXL_MX.h"

// Dynamixel register addresses common to all actuators
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

#define DXL_BYTE_ADDRESS_TYPE 0
#define DXL_WORD_L_ADDRESS_TYPE 1
#define DXL_WORD_H_ADDRESS_TYPE 2
#define DXL_UNDEFINED_ADDRESS_TYPE 3
#define DXL_NUM_ADDRESS 74

/*
 *	0:	Valid byte address, DXL_BYTE
 *	1:	First byte of valid word address, DXL_WORD_L
 *	2:	Second byte of valid word address, DXL_WORD_H
 *	3:	Invalid, unused, or undefined byte address, DXL_UNDEFINED
 */
static byte DXL_ADDRESS_TYPE[DXL_NUM_ADDRESS] = {
	1,2,	// 0-1
	0,		// 2
	0,		// 3
	0,		// 4
	0,		// 5
	1,2,	// 6-7
	1,2,	// 8-9
	3,		// 10
	0,		// 11
	0,		// 12
	0,		// 13
	1,2,	// 14-15
	0,		// 16
	0,		// 17
	0,		// 18
	3,		// 19
	
	1,2,	// 20-21
	0,		// 22
	3,		// 23
	
	0,		// 24
	0,		// 25
	
	0,		// 26
	0,		// 27
	0,		// 28
	3,		// 29
	
	1,2,	// 30-31
	1,2,	// 32-33
	1,2,	// 34-35
	1,2,	// 36-37
	1,2,	// 38-39
	1,2,	// 40-41
	0,		// 42
	0,		// 43
	0,		// 44
	3,		// 45
	0,		// 46
	0,		// 47
	1,2,	// 48-49
	
	3,		// 50
	3,		// 51
	3,		// 52
	3,		// 53
	3,		// 54
	3,		// 55
	3,		// 56
	3,		// 57
	3,		// 58
	3,		// 59
	3,		// 60
	3,		// 61
	3,		// 62
	3,		// 63
	3,		// 64
	3,		// 65
	3,		// 66
	3,		// 67
	
	1,2,	// 68-69
	0,		// 70
	1,2,	// 71-72
	
	0		// 73
};

#endif /* DXL_ADDRESS_H_ */