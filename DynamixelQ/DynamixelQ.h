/*
 *	DynamixelQ.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 10-3-14
 *
 *	Based on: Dynamixel.h by in2storm, 11-8-13, revised 11-12-13
 */

#ifndef DYNAMIXELQ_H_
#define DYNAMIXELQ_H_

#include <math.h>
#include "dxl.h"
#include "DXL_Address.h"

// Baud rates between OpenCM9.04 and Dynamixels
#define DXL_BAUD_9600 207
#define DXL_BAUD_57600 34
#define DXL_BAUD_115200 16
#define DXL_BAUD_1000000 1
#define DXL_BAUD_2000000 0
#define DXL_BAUD_3000000 252

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
#define DXL_USART_SR_TRANSMISSION_COMPLETE ((uint16)0x0040)

#define DXL_MAKEWORDQ(a, b) (a | (b << 8))
#define DXL_LOBYTEQ(w) (w & 0xFF)
#define DXL_HIBYTEQ(w) (w >> 8)

class DynamixelQ {
public:
	DynamixelQ(int DXL_Type);
	virtual ~DynamixelQ(void);

	void begin(uint32 baud);

	byte readByte(byte bID, byte bAddress);
	void readByte(const byte bID[], byte bIDLength, byte bAddress, byte bData[]);
	void readByte(const byte bID[], byte bIDLength, const byte bAddress[], byte bData[]);
	
	byte writeByte(byte bID, byte bAddress, byte bData);
	byte writeByte(const byte bID[], byte bIDLength, byte bAddress, byte bData);
	byte writeByte(const byte bID[], byte bIDLength, byte bAddress, const byte bData[]);

	word readWord(byte bID, byte bAddress);
	void readWord(const byte bID[], byte bIDLength, byte bAddress, word wData[]);
	void readWord(const byte bID[], byte bIDLength, const byte bAddress[], word wData[]);
	
	byte writeWord(byte bID, byte bAddress, word wData);
	byte writeWord(const byte bID[], byte bIDLength, byte bAddress, word wData);
	byte writeWord(const byte bID[], byte bIDLength, byte bAddress, const word wData[]);
	
	void syncRead(const byte bID, byte bStartAddress, byte bNumAddress, word wData[]);
	void syncRead(const byte bID[], byte bIDLength, byte bStartAddress, byte bNumAddress, word wData[]);
	
	byte syncWrite(byte bID, byte bStartAddress, const word wData[], byte bNumDataPerID);
	byte syncWrite(const byte bID[], byte bIDLength, byte bStartAddress, const word wData[], byte bNumDataPerID, byte bDataLength);
	
private:
	/*
	 *	Convert Dynamixel Data value to BPS value
	 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Actuator_Address_04
	 */
	inline uint32 getBaudRate(const byte baud) __attribute__((always_inline))
	{
		switch (baud) {
			case 250:
				return 2250000;
			case 251:
				return 2500000;
			case DXL_BAUD_3000000:
				return 3000000;
			default:
				return (baud < 250) ? 2000000/(baud + 1) : 0;
		}
	}


	/*
	 *	Returns 1 if an address start location is valid and stores a byte or low or high byte
	 *	of a word and 0 otherwise.
	 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
	 */
	inline byte isAddressValid(const byte bAddress) __attribute__((always_inline))
	{
		return (bAddress < DXL_NUM_ADDRESS && DXL_ADDRESS_TYPE[bAddress] != DXL_UNDEFINED);
	}

	/*
	 *	Returns 1 if an address start location is valid and stores a byte and 0 otherwise.
	 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
	 */
	inline byte isAddressByte(const byte bAddress) __attribute__((always_inline))
	{
		return (bAddress < DXL_NUM_ADDRESS && DXL_ADDRESS_TYPE[bAddress] == DXL_BYTE);
	}

	/*
	 *	Returns 1 if an address start location is valid and stores a word and 0 otherwise.
	 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
	 */
	inline byte isAddressWord(const byte bAddress) __attribute__((always_inline))
	{
		return (bAddress < DXL_NUM_ADDRESS && DXL_ADDRESS_TYPE[bAddress] == DXL_WORD_L);
	}

	void txPacket(byte bID, byte bInstruction, byte bParameterLength);
	byte rxPacket(byte bID, byte bRxLength);
	byte txRxPacket(byte bID, byte bInst, byte bTxParaLen);
	void writeRaw(uint8 value);

	inline void dxlTxEnable(void) __attribute__((always_inline))
	{
		if (this->mDirPort == 0) {
			return;
		}
		gpio_write_bit(this->mDirPort, this->mDirPin, 1);
	}

	inline void dxlTxDisable(void) __attribute__((always_inline))
	{
		if (this->mDirPort == 0) {
			return;
		}
		gpio_write_bit(this->mDirPort, this->mDirPin, 0);
	}

	inline void clearBuffer(void) __attribute__((always_inline))
	{
		this->mDxlDevice->read_pointer = this->mDxlDevice->write_pointer = 0;
	}

	uint32 Dummy(uint32 tmp);
	void nDelay(uint32 nTime);

	dxl_dev *mDxlDevice;	/* Dynamixel */
	usart_dev *mDxlUsart;	/* USART Device */
	gpio_dev *mTxPort;
	gpio_dev *mRxPort;
	gpio_dev *mDirPort;
	uint8 mTxPin;
	uint8 mRxPin;
	uint8 mDirPin;
	uint8 mRxBuffer[DXL_RX_BUF_SIZE];
	uint8 mParamBuffer[DXL_PARAMETER_BUF_SIZE];

	uint8 mDXLtxrxStatus;

	static const byte mPktIdIndex = 2;
	static const byte mPktLengthIndex = 3;
	static const byte mPktInstIndex = 4;
};

#endif /* DYNAMIXELQ_H_ */