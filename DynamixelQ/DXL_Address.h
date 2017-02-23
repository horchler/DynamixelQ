/*
 *	DXL_Address.h
 *	
 *	Author: Andrew D. Horchler, horchler @ gmail . com
 *	Created: 8-13-14, modified: 4-22-15
 */

#ifndef DXL_ADDRESS_H_
#define DXL_ADDRESS_H_

#include "DXL_AX.h"
#include "DXL_MX.h"

typedef enum DXL_SERIES{
	DXL_AX_SERIES = 0,
	DXL_MX_SERIES,
	DXL_UNKNOWN_SERIES
} DXL_SERIES;

typedef enum DXL_SERIES_TYPE{
	DXL_AX_SERIES_TYPE = 0,
	DXL_MX_SERIES_BASIC,
	DXL_MX_SERIES_ADVANCED,
	DXL_UNKNOWN_SERIES_TYPE
} DXL_SERIES_TYPE;

// Dynamixel register addresses common to all AX and MX series actuators
#define DXL_MODEL_NUMBER                   uint8(0)
#define DXL_VERSION_OF_FIRMWARE            uint8(2)
#define DXL_ID                             uint8(3)
#define DXL_BAUD_RATE                      uint8(4)
#define DXL_RETURN_DELAY_TIME              uint8(5)
#define DXL_CW_ANGLE_LIMIT                 uint8(6)
#define DXL_CCW_ANGLE_LIMIT                uint8(8)
#define DXL_THE_HIGHEST_LIMIT_TEMPERATURE uint8(11)
#define DXL_THE_LOWEST_LIMIT_VOLTAGE      uint8(12)
#define DXL_THE_HIGHEST_LIMIT_VOLTAGE     uint8(13)
#define DXL_MAX_TORQUE                    uint8(14)
#define DXL_STATUS_RETURN_LEVEL           uint8(16)
#define DXL_ALARM_LED                     uint8(17)
#define DXL_ALARM_SHUTDOWN                uint8(18)

#define DXL_TORQUE_ENABLE                 uint8(24)
#define DXL_LED                           uint8(25)

#define DXL_GOAL_POSITION                 uint8(30)
#define DXL_MOVING_SPEED                  uint8(32)
#define DXL_TORQUE_LIMIT                  uint8(34)
#define DXL_PRESENT_POSITION              uint8(36)
#define DXL_PRESENT_SPEED                 uint8(38)
#define DXL_PRESENT_LOAD                  uint8(40)
#define DXL_PRESENT_VOLTAGE               uint8(42)
#define DXL_PRESENT_TEMPERATURE           uint8(43)
#define DXL_REGISTERED                    uint8(44)
#define DXL_MOVING                        uint8(46)
#define DXL_LOCK                          uint8(47)
#define DXL_PUNCH                         uint8(48)

// Alternative names
#define DXL_HIGH_LIMIT_TEMPERATURE DXL_THE_HIGHEST_LIMIT_TEMPERATURE
#define DXL_LOW_LIMIT_VOLTAGE           DXL_THE_LOWEST_LIMIT_VOLTAGE
#define DXL_HIGH_LIMIT_VOLTAGE         DXL_THE_HIGHEST_LIMIT_VOLTAGE

/*
 *	0:	Valid byte address, DXL_BYTE
 *	1:	First byte of valid word address, DXL_WORD_L
 *	2:	Second byte of valid word address, DXL_WORD_H
 *	3:	Invalid, unused, or undefined byte address, DXL_UNDEFINED
 */
enum DXL_ADDRESS_TYPE{
	DXL_BYTE_ADDRESS_TYPE = 0,
	DXL_WORD_L_ADDRESS_TYPE,
	DXL_WORD_H_ADDRESS_TYPE,
	DXL_UNDEFINED_ADDRESS_TYPE
};
#define DXL_NUM_ADDRESS uint8(74)

static const byte DXL_ADDRESS[DXL_NUM_ADDRESS] = {
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, //   0-1
	DXL_BYTE_ADDRESS_TYPE,                           //     2
	DXL_BYTE_ADDRESS_TYPE,                           //     3
	DXL_BYTE_ADDRESS_TYPE,                           //     4
	DXL_BYTE_ADDRESS_TYPE,                           //     5
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, //   6-7
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, //   8-9
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    10
	DXL_BYTE_ADDRESS_TYPE,                           //    11
	DXL_BYTE_ADDRESS_TYPE,                           //    12
	DXL_BYTE_ADDRESS_TYPE,                           //    13
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 14-15
	DXL_BYTE_ADDRESS_TYPE,                           //    16
	DXL_BYTE_ADDRESS_TYPE,                           //    17
	DXL_BYTE_ADDRESS_TYPE,                           //    18
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    19
	
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 20-21**
	DXL_BYTE_ADDRESS_TYPE,                           //    22**
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    23
	
	DXL_BYTE_ADDRESS_TYPE,                           //    24
	DXL_BYTE_ADDRESS_TYPE,                           //    25
	
	DXL_BYTE_ADDRESS_TYPE,                           //    26
	DXL_BYTE_ADDRESS_TYPE,                           //    27
	DXL_BYTE_ADDRESS_TYPE,                           //    28
	DXL_BYTE_ADDRESS_TYPE,                           //    29*
	
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 30-31
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 32-33
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 34-35
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 36-37
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 38-39
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 40-41
	DXL_BYTE_ADDRESS_TYPE,                           //    42
	DXL_BYTE_ADDRESS_TYPE,                           //    43
	DXL_BYTE_ADDRESS_TYPE,                           //    44
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    45
	DXL_BYTE_ADDRESS_TYPE,                           //    46
	DXL_BYTE_ADDRESS_TYPE,                           //    47
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 48-49
	
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    50
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    51
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    52
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    53
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    54
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    55
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    56
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    57
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    58
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    59
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    60
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    61
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    62
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    63
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    64
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    65
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    66
	DXL_UNDEFINED_ADDRESS_TYPE,                      //    67
	
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 68-69***
	DXL_BYTE_ADDRESS_TYPE,                           //    70***
	DXL_WORD_L_ADDRESS_TYPE,DXL_WORD_H_ADDRESS_TYPE, // 71-72***
	
	DXL_BYTE_ADDRESS_TYPE                            //    73**
};

#endif /* DXL_ADDRESS_H_ */