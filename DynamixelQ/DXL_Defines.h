/*
 *	DXL_Defines.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 3-8-15, modified: 3-22-15
 */
 
#ifndef DXL_DEFINES_H_
#define DXL_DEFINES_H_

// Baud rates between OpenCM9.04 and Dynamixels
#define DXL_BAUD_9600 207
#define DXL_BAUD_19200 103
#define DXL_BAUD_57600 34
#define DXL_BAUD_115200 16
#define DXL_BAUD_200000 9
#define DXL_BAUD_250000 7
#define DXL_BAUD_400000 4
#define DXL_BAUD_500000 3
#define DXL_BAUD_1000000 1
#define DXL_BAUD_2000000 0
#define DXL_BAUD_2250000 250
#define DXL_BAUD_2500000 251
#define DXL_BAUD_3000000 252

#define DXL_BYTE_LENGTH 1
#define DXL_WORD_LENGTH 2
#define DXL_INVALID_BYTE 0xFF
#define DXL_INVALID_WORD 0xFFFF
#define DXL_MAX_PACKET_LENGTH 143
#define DXL_PACKET_HEADER_LENGTH 6
#define DXL_MAX_PARAM_BUFFER_LENGTH (DXL_MAX_PACKET_LENGTH-DXL_PACKET_HEADER_LENGTH-2)
#define DXL_MAX_IDS_PER_BYTE floor(DXL_MAX_PARAM_BUFFER_LENGTH/2)
#define DXL_MAX_IDS_PER_WORD floor(DXL_MAX_PARAM_BUFFER_LENGTH/3)
#define DXL_PACKET_HEADER 0xFF
#define DXL_CHECKSUM_MASK 0xFF
#define DXL_USART_DR_PARITY_MASK ((uint16)0x01FF)

#define DXL_MAKEWORDQ(a, b) (a | (b << 8))
#define DXL_LOBYTEQ(w) (w & 0xFF)
#define DXL_HIBYTEQ(w) (w >> 8)
#define DXL_MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define DXL_MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })

#define DXL_MAX_ID 0xFC

#define DXL_MAX_RETURN_DELAY_TIME 0xFE
#define DXL_USEC_PER_RETURN_DELAY_TIME 2

#define DXL_MIN_LIMIT_VOLTAGE 0x32
#define DXL_MAX_LIMIT_VOLTAGE 0x96
#define DXL_MV_PER_LIMIT_VOLTAGE 100

// TODO. These two items must be manually changed to properly handle AX-series actuators
#define DXL_POSITION_RESOLUTION DXL_MX_POSITION_RESOLUTION
#define DXL_MAX_TORQUE_LIMIT DXL_MX_MAX_TORQUE_LIMIT

#define DXL_PERCENT_MAX_TORQUE_PER_LOAD_MAGNITUDE (1.0/DXL_MAX_TORQUE_LIMIT)

#endif /* DXL_DEFINES_H_ */