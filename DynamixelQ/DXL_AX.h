/*
 *	DXL_AX.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 4-23-15
 */

#ifndef DXL_AX_H_
#define DXL_AX_H_

// AX Series model numbers
enum DXL_AX_MODELS{
	DXL_AX12  =  uint16(12), // 0x000C
	DXL_AX18  =  uint16(18), // 0x0012
	DXL_AX12W = uint16(300)  // 0x012C
};

#define DXL_AX_NUM_ADDRESS uint8(0x31)

// Limiting values
#define DXL_AX_MAX_BAUD uint8(1)

#define DXL_AX_MIN_COMPLIANCE_SLOPE uint8(0x02)
#define DXL_AX_MAX_COMPLIANCE_SLOPE uint8(0x80)

#define DXL_AX_POSITION_RESOLUTION            uint16(0x03FF)
#define DXL_AX_MAX_MAX_MOVING_SPEED_MAGNITUDE uint16(0x03FF)

// Conversions
#define DXL_AX_COMPLIANCE_SLOPE(x) (1<<uint8(log2(DXL_MAX(x, DXL_AX_MIN_COMPLIANCE_SLOPE))))

#define DXL_AX_RADIANS_PER_TICK (2.0*M_PI/DXL_AX_POSITION_RESOLUTION)
#define DXL_AX_DEGREES_PER_TICK (360.0/DXL_AX_POSITION_RESOLUTION)

// Dynamixel register addresses for AX series
#define DXL_CW_COMPLIANCE_MARGIN  uint8(26)
#define DXL_CCW_COMPLIANCE_MARGIN uint8(27)
#define DXL_CW_COMPLIANCE_SLOPE   uint8(28)
#define DXL_CCW_COMPLIANCE_SLOPE  uint8(29)

#endif /* DXL_AX_H_ */