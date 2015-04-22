/*
 *	DXL_Defines.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 3-8-15, modified: 4-22-15
 */
 
#ifndef DXL_DEFINES_H_
#define DXL_DEFINES_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"
#include "gpio.h"
#include "DXL_Address.h"

// Prevent dxl.h from being included, if present
#define DXL2_H_

#define DXL_RX_BUF_SIZE        0x3FF
#define DXL_PARAMETER_BUF_SIZE   128

#define DXL_RX_TIMEOUT_COUNT   1600U

#define PORT_TXRX_DIRECTION    GPIOB
#define PIN_TXRX_DIRECTION         5

#define PORT_DXL_TXD           GPIOB
#define PORT_DXL_RXD           GPIOB

#define PIN_DXL_TXD                6
#define PIN_DXL_RXD                7

typedef struct dxl_dev {
	uint16 write_pointer;
	uint16 read_pointer;
	uint8 data_buffer[DXL_RX_BUF_SIZE];
	voidFuncPtrUart handlers;
} dxl_dev;
extern dxl_dev *DXL_DEV1;

#define BROADCAST_ID 		 uint8(0xFE)
#define DXL_BROADCAST_ID 	BROADCAST_ID
#define DXL_MAX_ID   		 uint8(0xFC)
#define DXL_MAX_ACTUATORS (DXL_MAX_ID+1)

// Instruction commands
typedef enum DXL_INSTRUCTION{
	INST_PING          =   1,
	INST_READ          =   2,
	INST_WRITE         =   3,
	INST_REG_WRITE     =   4,
	INST_ACTION        =   5,
	INST_FACTORY_RESET =   6,
	INST_REBOOT        =   8,
	INST_SYSTEM_WRITE  =  13, // 0x0D
	INST_STATUS        =  85, // 0x55
	INST_SYNC_READ     = 130, // 0x82
	INST_SYNC_WRITE    = 131, // 0x83
	INST_BULK_READ     = 146, // 0x92
	INST_BULK_WRITE    = 147  // 0x93
} DXL_INSTRUCTION;
/*
#define INST_RESET          0x06
#define INST_DIGITAL_RESET  0x07
#define INST_SYSTEM_READ    0x0C
#define INST_SYNC_REG_WRITE 0x84
*/

// DXL_ALARM_LED and DXL_ALARM_SHUTDOWN error messages for 1.0 protocol
enum DXL_ALARM_ERROR{
	DXL_ALARM_ERROR_BIT_VOLTAGE     =  1,
	DXL_ALARM_ERROR_BIT_ANGLE       =  2,
	DXL_ALARM_ERROR_BIT_OVERHEAT    =  4,
	DXL_ALARM_ERROR_BIT_RANGE       =  8,
	DXL_ALARM_ERROR_BIT_CHECKSUM    = 16,
	DXL_ALARM_ERROR_BIT_OVERLOAD    = 32,
	DXL_ALARM_ERROR_BIT_INSTRUCTION = 64
};
#define DXL_MAX_ALARM_ERROR uint8(0x7F)

// Communication messages
#define	COMM_TXSUCCESS 0
#define COMM_RXSUCCESS 1
#define COMM_TXFAIL    2
#define COMM_RXFAIL    3
#define COMM_TXERROR   4
#define COMM_RXWAITING 5
#define COMM_RXTIMEOUT 6
#define COMM_RXCORRUPT 7

typedef enum DXL_BOOL{
	DXL_FALSE = 0,
	DXL_TRUE
} DXL_BOOL;

enum DXL_LED_STATE{
	DXL_LED_OFF = 0,
	DXL_LED_ON
};

enum DXL_RETURN{
	DXL_FAILURE = 0,
	DXL_SUCCESS
};

// DXL_STATUS_RETURN_LEVEL options
enum DXL_STATUS_RETURN_VALUE{
	DXL_STATUS_RETURN_NONE      =    0,
	DXL_STATUS_RETURN_READ_ONLY =    1,
	DXL_STATUS_RETURN_ALL       =    2,
	DXL_STATUS_RETURN_UNKNOWN   = 0xFF
};

enum DXL_CONTROL_MODE{
	DXL_JOINT_MODE = 0,
	DXL_WHEEL_MODE,
	DXL_MULTI_TURN_MODE,
	DXL_TORQUE_CONTROL_MODE,
	DXL_UNKNOWN_MODE
};

// DXL_BAUD_RATE baud rates between OpenCM9.04 and Dynamixels
typedef enum DXL_BAUD_RATE_VALUE{
	DXL_BAUD_9600    = 207,
	DXL_BAUD_19200   = 103,
	DXL_BAUD_57600   =  34,
	DXL_BAUD_115200  =  16,
	DXL_BAUD_200000  =   9,
	DXL_BAUD_250000  =   7,
	DXL_BAUD_400000  =   4,
	DXL_BAUD_500000  =   3,
	DXL_BAUD_1000000 =   1,
	DXL_BAUD_2000000 =   0,
	DXL_BAUD_2250000 = 250,
	DXL_BAUD_2500000 = 251,
	DXL_BAUD_3000000 = 252
} DXL_BAUD_RATE_VALUE;

// Packet properties
#define DXL_BYTE_LENGTH uint8(1)
#define DXL_WORD_LENGTH uint8(2)
#define DXL_INVALID_BYTE uint8(0xFF)
#define DXL_INVALID_WORD uint16(0xFFFF)
#define DXL_MAX_PACKET_LENGTH uint8(143)
#define DXL_PACKET_HEADER_LENGTH uint8(6)
#define DXL_READ_WRITE_MIN_PARMETER_LENGTH uint8(2)
#define DXL_SYNC_WRITE_MIN_PARMETER_LENGTH uint8(4)
#define DXL_MAX_PARAM_BUFFER_LENGTH (DXL_MAX_PACKET_LENGTH-DXL_PACKET_HEADER_LENGTH-DXL_SYNC_WRITE_MIN_PARMETER_LENGTH)
#define DXL_MAX_IDS_PER_BYTE uint8(DXL_MAX_PARAM_BUFFER_LENGTH/2)
#define DXL_MAX_IDS_PER_WORD uint8(DXL_MAX_PARAM_BUFFER_LENGTH/3)
#define DXL_PACKET_HEADER uint8(0xFF)
#define DXL_CHECKSUM_MASK uint8(0xFF)
#define DXL_USART_DR_PARITY_MASK uint16(0x01FF)

#define DXL_UNINTIALIZED_BYTE DXL_INVALID_BYTE
#define DXL_UNINTIALIZED_WORD DXL_INVALID_WORD

// Macros
#define DXL_MAKEWORD(a, b) (a | (b << 8))
#define DXL_LOBYTE(w) (w & 0xFF)
#define DXL_HIBYTE(w) (w >> 8)
#define DXL_MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define DXL_MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })

// Limiting values
#define DXL_MAX_RETURN_DELAY_TIME    uint8(0xFE)

#define DXL_MIN_LIMIT_VOLTAGE        uint8(0x32)
#define DXL_MAX_LIMIT_VOLTAGE        uint8(0x96)

#define DXL_MAX_TORQUE_LIMIT      uint16(0x03FF)

#define DXL_MAX_PUNCH             uint16(0x03FF)

// Conversions
#define DXL_MICROSECOND_PER_RETURN_DELAY_TIME   2
#define DXL_MILLIVOLT_PER_LIMIT_VOLTAGE       100

#ifdef __cplusplus
}
#endif
#endif /* DXL_DEFINES_H_ */