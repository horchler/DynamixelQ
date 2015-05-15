/*
 *	DXL_MX.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 5-15-15
 */

#ifndef DXL_MX_H_
#define DXL_MX_H_

// MX Series model numbers
enum DXL_MX_MODELS{
	DXL_MX12W = uint16(360), // 0x0168
	DXL_MX28  =  uint16(29), // 0x001D
	DXL_MX64  = uint16(310), // 0x0136
	DXL_MX106 = uint16(320)  // 0x0140
};

#define DXL_MX_NUM_ADDRESS DXL_NUM_ADDRESS

// Limiting values
#define DXL_MX_MAX_BAUD uint8(252)

#define DXL_MX_MAX_MULTI_TURN_OFFSET_MAGNITUDE uint16(0x6000)
#define DXL_MX_MIN_RESOLUTION_DIVIDER             uint8(0x01)
#define DXL_MX_MAX_RESOLUTION_DIVIDER             uint8(0x04)

#define DXL_MX_MAX_GAIN uint8(0xFE)

#define DXL_MX_POSITION_RESOLUTION            uint16(0x0FFF)
#define DXL_MX_MAX_MAX_MOVING_SPEED_MAGNITUDE uint16(0x03FF)

#define DXL_MX_MAX_CURRENT      uint16(0xFFFF)
#define DXL_MX_MAX_GOAL_TORQUE  uint16(0x07FF)
#define DXL_MX_MAX_ACCELERATION    uint8(0xFE)

// Conversions
#define DXL_MX_RADIANS_PER_TICK (2.0*M_PI/DXL_MX_POSITION_RESOLUTION)
#define DXL_MX_DEGREES_PER_TICK    (360.0/DXL_MX_POSITION_RESOLUTION)

#define DXL_MX_MICROAMPS_PER_TORQUE 4500

#define DXL_MX_RADIANS_PER_SECOND_SQUARED_PER_TICK (2180.0*M_PI/(180.0*DXL_MX_MAX_ACCELERATION))
#define DXL_MX_DEGREES_PER_SECOND_SQUARED_PER_TICK              (2180.0/DXL_MX_MAX_ACCELERATION)

// Dynamixel register addresses for MX series
#define DXL_MULTI_TURN_OFFSET  uint8(20)
#define DXL_RESOLUTION_DIVIDER uint8(22)

#define DXL_D_GAIN uint8(26)
#define DXL_I_GAIN uint8(27)
#define DXL_P_GAIN uint8(28)

// DXL_MX64 and DXL_MX106 only
#define DXL_CURRENT                    uint8(68)
#define DXL_TORQUE_CONTROL_MODE_ENABLE uint8(70)
#define DXL_GOAL_TORQUE                uint8(71)

#define DXL_GOAL_ACCELERATION          uint8(73)

#endif /* DXL_MX_H_ */