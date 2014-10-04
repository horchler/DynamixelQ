/*
 *	DXL_AX.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 10-3-14
 */

#ifndef DXL_AX_H_
#define DXL_AX_H_

#define DXL_AX_SERIES 1
#define DXL_AX12 2
#define DXL_AX18 3

#define DXL_AX_MAX_BAUD 1

#define DXL_AX_POSITION_RESOLUTION 0x07FF
#define DXL_AX_MAX_MAX_MOVING_SPEED_MAGNITUDE 0x03FF
#define DXL_AX_MAX_TORQUE_LIMIT 0x03FF

#define DXL_AX_RADIANS_PER_TICK (2.0*M_PI/DXL_AX_POSITION_RESOLUTION)
#define DXL_AX_DEGREES_PER_TICK (360.0/DXL_AX_POSITION_RESOLUTION)

// Dynamixel register addresses for AX series
#define DXL_CW_COMPLIANCE_MARGIN 26
#define DXL_CCW_COMPLIANCE_MARGIN 27
#define DXL_CW_COMPLIANCE_SLOPE 28
#define DXL_CCW_COMPLIANCE_SLOPE 29

#endif /* DXL_AX_H_ */