/*
 *	DynamixelQ.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 3-23-15
 *
 *	Based on: Dynamixel.h by in2storm, 11-8-13, revised 11-12-13
 */

#ifndef DYNAMIXELQ_H_
#define DYNAMIXELQ_H_

#include <math.h>
#include "delay.h"
#include "dxl.h"
#include "DXL_Address.h"
#include "DXL_Defines.h"

class DynamixelQ {
public:
	DynamixelQ(byte DXL_Type);
	virtual ~DynamixelQ(void);
	
	void begin(byte baud);
	
	inline byte available(void) __attribute__((always_inline))
	{
		return this->mDxlDevice->write_pointer != this->mDxlDevice->read_pointer;
	}
	inline uint8 readRaw(void) __attribute__((always_inline))
	{
		return this->mDxlDevice->data_buffer[this->mDxlDevice->read_pointer++ & DXL_RX_BUF_SIZE];
	}
	void writeRaw(uint8 value);
	void writeRaw(const uint8 *value, byte len);
	
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
	
	byte syncWrite(byte bStartAddress, const word wData[], byte bNumData);
	byte syncWrite(byte bID, byte bStartAddress, const word wData[], byte bNumData);
	byte syncWrite(const byte bID[], byte bIDLength, byte bStartAddress, const word wData[], byte bNumDataPerID, byte bDataLength);
	
	// DXL_Utils
	
	inline word getModel(byte bID);
	inline void getModel(const byte bID[], byte bIDLength, word wModelNumber[]);
	
	inline byte getFirmware(byte bID);
	inline void getFirmware(const byte bID[], byte bIDLength, byte bFirmwareVersion[]);
	
	inline byte isID(byte bID);
	byte isID(const byte bID[], byte bIDLength);
	void isID(const byte bID[], byte bIDLength, byte bBoolean[]);
	
	inline byte getBaudRate(byte bID);
	inline void getBaudRate(const byte bID[], byte bIDLength, byte bBaudeRate[]);
	
	byte getReturnDelay(byte bID);
	void getReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay[]);
	
	inline byte setReturnDelay(byte bReturnDelay);
	inline byte setReturnDelay(byte bID, byte bReturnDelay);
	inline byte setReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay);
	byte setReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay[]);
	
	/*
	inline word getCWAngleLimit(byte bID);
	inline word getCCWAngleLimit(byte bID);
	inline byte getHighTemperatureLimit(byte bID);
	inline byte getLowTemperatureLimit(byte bID);
	inline byte getHighVoltageLimit(byte bID);
	inline word getMaxTorque(byte bID);
	inline byte getStatusReturnLevel(byte bID);
	inline byte getAlarmLED(byte bID);
	inline byte getAlarmShutdown(byte bID);
	inline word getMultiTurnOffset(byte bID);
	inline byte getResolutionDivider(byte bID);
	inline byte isTorqueEnabled(byte bID);
	*/
	
	inline byte getLED(byte bID);
	inline void getLED(const byte bID[], byte bIDLength, byte bLEDstate[]);
	
	inline byte setLED(byte bLEDstate);
	inline byte setLED(byte bID, byte bLEDstate);
	inline byte setLED(const byte bID[], byte bIDLength, byte bLEDstate);
	byte setLED(const byte bID[], byte bIDLength, byte bLEDstate[]);
	
	byte toggleLED(byte bLEDstate);
	void toggleLED(const byte bID[], byte bIDLength);
	
	/*
	byte blinkLED(byte bID, unsigned long usOnTime, unsigned long usOffTime);
	void blinkLED(const byte bID[], byte bIDLength, unsigned long usOnTime, unsigned long usOffTime);
	
	inline byte getDGain(byte bID);
	inline byte getIGain(byte bID);
	inline byte getPGain(byte bID);
	*/
	
	inline word getPosition(byte bID);
	inline void getPosition(const byte bID[], byte bIDLength, word wPosition[]);
	
	inline byte setPosition(word wPosition);
	inline byte setPosition(byte bID, word wPosition);
	inline byte setPosition(const byte bID[], byte bIDLength, word wPosition);
	inline byte setPosition(const byte bID[], byte bIDLength, const word wPosition[]);
	
	inline word getSpeed(byte bID);
	inline void getSpeed(const byte bID[], byte bIDLength, word wSpeed[]);
	
	inline byte setSpeed(word wSpeed);
	inline byte setSpeed(byte bID, word wSpeed);
	inline byte setSpeed(const byte bID[], byte bIDLength, word wSpeed);
	inline byte setSpeed(const byte bID[], byte bIDLength, const word wSpeed[]);
	
	inline word getLoad(byte bID);
	inline void getLoad(const byte bID[], byte bIDLength, word wLoad[]);
	
	inline byte setLoad(word wLoad);
	inline byte setLoad(byte bID, word wLoad);
	inline byte setLoad(const byte bID[], byte bIDLength, word wLoad);
	inline byte setLoad(const byte bID[], byte bIDLength, const word wLoad[]);
	
	/*
	inline byte getTemperature(byte bID);
	inline byte isRegistered(byte bID);
	*/
	
	inline byte isMoving(byte bID);
	byte isMoving(const byte bID[], byte bIDLength);
	inline void isMoving(const byte bID[], byte bIDLength, byte bBoolean[]);
	
	/*
	inline byte isLocked(byte bID);
	inline word getPunch(byte bID);
	inline word getCurrent(byte bID);
	inline word getGoalTorque(byte bID);
	inline byte getGoalAcceleration(byte bID);
	*/
	
	inline byte setJointMode(void);
	byte setJointMode(byte bID);
	byte setJointMode(const byte bID[], byte bIDLength);
	
	inline byte setWheelMode(void);
	byte setWheelMode(byte bID);
	byte setWheelMode(const byte bID[], byte bIDLength);
	
	inline byte setMultiTurnMode(void);
	byte setMultiTurnMode(byte bID);
	byte setMultiTurnMode(const byte bID[], byte bIDLength);
	/*
	byte setTorqueControlMode(void);
	byte setTorqueControlMode(byte bID);
	byte setTorqueControlMode(const byte bID[], byte bIDLength);
	
	byte getMode(byte bID);
	void getMode(const byte bID[], byte bIDLength, byte bMode[]);
	
	byte isJointMode(byte bID);
	void isJointMode(const byte bID[], byte bIDLength, byte bBoolean[]);
	
	byte isWheelMode(byte bID);
	void isWheelMode(const byte bID[], byte bIDLength, byte bBoolean[]);
	
	byte isMultiTurnMode(byte bID);
	void isMultiTurnMode(const byte bID[], byte bIDLength, byte bBoolean[]);
	*/
	
	inline byte zeroSpeed(void);
	inline byte zeroSpeed(byte bID);
	inline byte zeroSpeed(const byte bID[], byte bIDLength);
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