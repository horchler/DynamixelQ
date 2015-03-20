/*
 *	DynamixelQ.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 3-20-15
 *
 *	Based on: Dynamixel.h by in2storm, 11-8-13, revised 11-12-13
 */

#ifndef DYNAMIXELQ_H_
#define DYNAMIXELQ_H_

#include <math.h>
#include "dxl.h"
#include "DXL_Address.h"
#include "DXL_Defines.h"

class DynamixelQ {
public:
	DynamixelQ(byte DXL_Type);
	virtual ~DynamixelQ(void);
	
	void begin(byte baud);
	/*
	byte available(void);
	byte readRaw(void);
	void writeRaw(const byte bValue);
	void writeRaw(const uint8 *value, uint8 len);
	*/
	byte readByte(byte bID, byte bAddress);
	void readByte(const byte bID[], byte bIDLength, byte bAddress, byte bData[]);
	void readByte(const byte bID[], byte bIDLength, const byte bAddress[], byte bData[]);
	
	byte writeByte(byte bAddress, byte bData);
	byte writeByte(byte bID, byte bAddress, byte bData);
	byte writeByte(const byte bID[], byte bIDLength, byte bAddress, byte bData);
	byte writeByte(const byte bID[], byte bIDLength, byte bAddress, const byte bData[]);
	
	word readWord(byte bID, byte bAddress);
	void readWord(const byte bID[], byte bIDLength, byte bAddress, word wData[]);
	void readWord(const byte bID[], byte bIDLength, const byte bAddress[], word wData[]);
	
	byte writeWord(byte bAddress, word wData);
	byte writeWord(byte bID, byte bAddress, word wData);
	byte writeWord(const byte bID[], byte bIDLength, byte bAddress, word wData);
	byte writeWord(const byte bID[], byte bIDLength, byte bAddress, const word wData[]);
	
	void syncRead(const byte bID, byte bStartAddress, byte bNumAddress, word wData[]);
	void syncRead(const byte bID[], byte bIDLength, byte bStartAddress, byte bNumAddress, word wData[]);
	
	byte syncWrite(byte bStartAddress, const word wData[], byte bNumDataPerID);
	byte syncWrite(byte bID, byte bStartAddress, const word wData[], byte bNumDataPerID);
	byte syncWrite(const byte bID[], byte bIDLength, byte bStartAddress, const word wData[], byte bNumDataPerID, byte bDataLength);
	
	// DXL_Utils
	/*
	word getModelNumber(byte bID);
	byte getFirmwareVersion(byte bID);
	byte getID(byte bID);
	byte getBaudRate(byte bID);
	
	byte getReturnDelay(byte bID);
	void getReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay[]);
	*/
	byte setReturnDelay(byte bReturnDelay);
	byte setReturnDelay(byte bID, byte bReturnDelay);
	byte setReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay);
	byte setReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay[]);
	/*
	word getCWAngleLimit(byte bID);
	word getCCWAngleLimit(byte bID);
	byte getHighTemperatureLimit(byte bID);
	byte getLowTemperatureLimit(byte bID);
	byte getHighVoltageLimit(byte bID);
	word getMaxTorque(byte bID);
	byte getStatusReturnLevel(byte bID);
	byte getAlarmLED(byte bID);
	byte getAlarmShutdown(byte bID);
	*/
	word getPosition(byte bID);
	void getPosition(const byte bID[], byte bIDLength, word wPosition[]);
	
	byte setPosition(word wPosition);
	byte setPosition(byte bID, word wPosition);
	byte setPosition(const byte bID[], byte bIDLength, word wPosition);
	byte setPosition(const byte bID[], byte bIDLength, const word wPosition[]);
	
	word getSpeed(byte bID);
	void getSpeed(const byte bID[], byte bIDLength, word wSpeed[]);
	
	byte setSpeed(word wSpeed);
	byte setSpeed(byte bID, word wSpeed);
	byte setSpeed(const byte bID[], byte bIDLength, word wSpeed);
	byte setSpeed(const byte bID[], byte bIDLength, const word wSpeed[]);
	
	word getLoad(byte bID);
	void getLoad(const byte bID[], byte bIDLength, word wLoad[]);
	
	byte setLoad(word wLoad);
	byte setLoad(byte bID, word wLoad);
	byte setLoad(const byte bID[], byte bIDLength, word wLoad);
	byte setLoad(const byte bID[], byte bIDLength, const word wLoad[]);
	
	
	byte setJointMode(void);
	byte setJointMode(byte bID);
	byte setJointMode(const byte bID[], byte bIDLength);
	
	byte setWheelMode(void);
	byte setWheelMode(byte bID);
	byte setWheelMode(const byte bID[], byte bIDLength);
	
	byte setMultiTurnMode(void);
	byte setMultiTurnMode(byte bID);
	byte setMultiTurnMode(const byte bID[], byte bIDLength);
	/*
	byte setTorqueControlMode(void);
	byte setTorqueControlMode(byte bID);
	byte setTorqueControlMode(const byte bID[], byte bIDLength);
	
	byte getMode(byte bID);
	void getMode(const byte bID[], byte bIDLength, byte bMode[]);
	*/
	byte isID(byte bID);
	byte isID(const byte bID[], byte bIDLength);
	void isID(const byte bID[], byte bIDLength, byte bBoolean[]);
	/*
	byte isJointMode(byte bID);
	void isJointMode(const byte bID[], byte bIDLength, byte bBoolean[]);
	
	byte isWheelMode(byte bID);
	void isWheelMode(const byte bID[], byte bIDLength, byte bBoolean[]);
	
	byte isMultiTurnMode(byte bID);
	void isMultiTurnMode(const byte bID[], byte bIDLength, byte bBoolean[]);
	*/
	byte isMoving(byte bID);
	byte isMoving(const byte bID[], byte bIDLength);
	void isMoving(const byte bID[], byte bIDLength, byte bBoolean[]);
	
	byte zeroSpeed(void);
	byte zeroSpeed(byte bID);
	byte zeroSpeed(const byte bID[], byte bIDLength);
private:
	/*
	 *	Convert Dynamixel Data value to BPS value
	 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Actuator_Address_04
	 */
	inline uint32 convertBaudRate(const byte baud) __attribute__((always_inline))
	{
		switch (baud) {
			case DXL_BAUD_2250000:
				return 2250000U;
			case DXL_BAUD_2500000:
				return 2500000U;
			case DXL_BAUD_3000000:
				return 3000000U;
			default:
				return (baud < DXL_BAUD_2250000) ? 2000000/(baud + 1) : 0;
		}
	}

	/*
	 *	Returns 1 if an address start location is valid and stores a byte or low or high
	 *	byte of a word and 0 otherwise.
	 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
	 */
	inline byte isAddressValid(const byte bAddress) __attribute__((always_inline))
	{
		return (bAddress < DXL_NUM_ADDRESS && DXL_ADDRESS_TYPE[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
	}
	
	/*
	 *	Returns 1 if an address start location is valid and stores a byte and 0 otherwise.
	 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
	 */
	inline byte isAddressByte(const byte bAddress) __attribute__((always_inline))
	{
		return (bAddress < DXL_NUM_ADDRESS && DXL_ADDRESS_TYPE[bAddress] == DXL_BYTE_ADDRESS_TYPE);
	}
	
	/*
	 *	Returns 1 if an address start location is valid and stores a word and 0 otherwise.
	 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
	 */
	inline byte isAddressWord(const byte bAddress) __attribute__((always_inline))
	{
		return (bAddress < DXL_NUM_ADDRESS && DXL_ADDRESS_TYPE[bAddress] == DXL_WORD_L_ADDRESS_TYPE);
	}
	
	inline byte available(void) __attribute__((always_inline))
	{
		return this->mDxlDevice->write_pointer != this->mDxlDevice->read_pointer;
	}
	inline byte readRaw(void) __attribute__((always_inline))
	{
		return this->mDxlDevice->data_buffer[this->mDxlDevice->read_pointer++ & DXL_RX_BUF_SIZE];
	}
	
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
	
	void clearBuffer(void)
	{
		this->mDxlDevice->read_pointer = this->mDxlDevice->write_pointer = 0;
	}
	
	void writeRaw(uint8 value);
	void writeRaw(const uint8 *value, uint8 len);
	
	void txPacket(byte bID, byte bInstruction, byte bParameterLength);
	byte rxPacket(byte bID, byte bRxLength);
	byte txRxPacket(byte bID, byte bInst, byte bTxParaLen);
	void nsDelay(uint32 nsTime);
	
	dxl_dev *mDxlDevice;	/* Dynamixel */
	usart_dev *mDxlUsart;	/* USART Device */
	gpio_dev *mTxPort;
	gpio_dev *mRxPort;
	gpio_dev *mDirPort;
	uint8 mTxPin;
	uint8 mRxPin;
	uint8 mDirPin;
	uint8 mTxBuffer[DXL_RX_BUF_SIZE];
	uint8 mRxBuffer[DXL_RX_BUF_SIZE];
	uint8 mParamBuffer[DXL_PARAMETER_BUF_SIZE];
	
	uint8 mDXLtxrxStatus;
	
	static const byte mPktIdIndex = 2;
	static const byte mPktLengthIndex = 3;
	static const byte mPktInstIndex = 4;
};

#endif /* DYNAMIXELQ_H_ */