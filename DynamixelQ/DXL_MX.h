/*
 *	DXL_MX.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 10-22-15
 */

#ifndef DXL_MX_H_
#define DXL_MX_H_

#define DXL_MX_SERIES 10
#define DXL_MX12 11
#define DXL_MX28 12
#define DXL_MX64 13
#define DXL_MX106 14

#define DXL_MX_MAX_BAUD 252

#define DXL_MX_POSITION_RESOLUTION 0x0FFF
#define DXL_MX_MAX_MAX_MOVING_SPEED_MAGNITUDE 0x03FF
#define DXL_MX_MAX_TORQUE_LIMIT 0x03FF
#define DXL_MX_MAX_ACCELERATION 0xFE

#define DXL_MX_RADIANS_PER_TICK (2.0*M_PI/DXL_MX_POSITION_RESOLUTION)
#define DXL_MX_DEGREES_PER_TICK (360.0/DXL_MX_POSITION_RESOLUTION)

// Dynamixel register addresses for MX series
#define DXL_MULTI_TURN_OFFSET uint8(20)
#define DXL_RESOLUTION_DIVIDER uint8(22)

#define DXL_MULTI_TURN_MAX_OFFSET_MAGNITUDE 0x6000
#define DXL_MULTI_TURN_MAX_RESOLUTION_DIVIDER 0x04

#define DXL_D_GAIN uint8(26)
#define DXL_I_GAIN uint8(27)
#define DXL_P_GAIN uint8(28)

// DXL_MX64 and DXL_MX106 only
#define DXL_CURRENT uint8(68)
#define DXL_TORQUE_CONTROL_MODE_ENABLE uint8(69)
#define DXL_GOAL_TORQUE uint8(71)

#define DXL_GOAL_ACCELERATION uint8(73)

#endif /* DXL_MX_H_ */