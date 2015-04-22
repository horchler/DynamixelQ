/*
 *	DXL_Utils.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 2-23-15, modified: 4-22-15
 */
 
#ifndef DXL_UTILS_H_
#define DXL_UTILS_H_

#include "DXL_Validate.h"

#define DXL_UTILS_RETRY_NSDELAY 1L

static int DXL_UTILS_RETRY_COUNT = 0;


inline int DXLQ::getRetryCount(void)
{
	return DXL_UTILS_RETRY_COUNT;
}

inline void DXLQ::setRetryCount(int retryCount)
{
	DXL_UTILS_RETRY_COUNT = retryCount;
}


inline void DXLQ::fillByteArray(byte bArray[], const byte bArrayLength, const byte bValue)
{
	byte i;
	
	for (i = 0; i < bArrayLength; i++) {
		bArray[i] = bValue;
	} 
}

inline void DXLQ::fillWordArray(word wArray[], const byte bArrayLength, const word wValue)
{
	byte i;
	
	for (i = 0; i < bArrayLength; i++) {
		wArray[i] = wValue;
	} 
}


inline byte DXLQ::doPing(const byte bID)
{
	int retryCount = 0;
	byte bStatus;
	
	if (bID <= DXL_MAX_ID) {
		bStatus = this->txRxPacket(bID, INST_PING, 0);
		while (retryCount < DXL_UTILS_RETRY_COUNT && !bStatus) {
			this->nsDelay(DXL_UTILS_RETRY_NSDELAY);
			bStatus = this->txRxPacket(bID, INST_PING, 0);
			retryCount++;
		}
		return bStatus ? this->mRxBuffer[2] : DXL_INVALID_BYTE;
	}
	return DXL_INVALID_BYTE;
}

void DXLQ::doPing(const byte bID[], const byte bIDLength, byte bPingID[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bPingID[i] = this->doPing(bID[i]);
	}
}


byte DXLQ::getByteData(const byte bID)
{
	int retryCount = 0;
	byte bStatus;
	
	if (bID <= DXL_MAX_ID) {
		bStatus = this->txRxPacket(bID, INST_READ, 2);
		while (retryCount < DXL_UTILS_RETRY_COUNT && !bStatus) {
			this->nsDelay(DXL_UTILS_RETRY_NSDELAY);
			bStatus = this->txRxPacket(bID, INST_READ, 2);
			retryCount++;
		}
		return bStatus ? this->mRxBuffer[5] : DXL_INVALID_BYTE;
	}
	return DXL_INVALID_BYTE;
}

word DXLQ::getWordData(const byte bID)
{
	int retryCount = 0;
	byte bStatus;
	
	if (bID <= DXL_MAX_ID) {
		bStatus = this->txRxPacket(bID, INST_READ, 2);
		while (retryCount < DXL_UTILS_RETRY_COUNT && !bStatus) {
			this->nsDelay(DXL_UTILS_RETRY_NSDELAY);
			bStatus = this->txRxPacket(bID, INST_READ, 2);
			retryCount++;
		}
		return bStatus ? DXL_MAKEWORD(this->mRxBuffer[5], this->mRxBuffer[6]) : DXL_INVALID_WORD;
	}
	return DXL_INVALID_WORD;
}


byte DXLQ::setData(const byte bID, const DXL_INSTRUCTION bInstruction, const byte bParamLen)
{
	int retryCount = 0;
	byte bStatus;
	
	bStatus = this->txRxPacket(bID, bInstruction, bParamLen);
	while (retryCount < DXL_UTILS_RETRY_COUNT && !bStatus) {
		this->nsDelay(DXL_UTILS_RETRY_NSDELAY);
		bStatus = this->txRxPacket(bID, bInstruction, bParamLen);
		retryCount++;
	}
	return bStatus;
}


/*
 *	For the single bID, the byte value parameter stored at bAddress is returned.
 */
byte DXLQ::getByte(const byte bID, const byte bAddress)
{
	if (bID <= DXL_MAX_ID && (this->isByteAddress(bID, bAddress))) {
		this->mParamBuffer[0] = bAddress;
		this->mParamBuffer[1] = DXL_BYTE_LENGTH;
		return this->getByteData(bID);
	}
	return DXL_INVALID_BYTE;
}

/*
 *	For each of the bIDLength IDs in bID, the byte value parameter stored at bAddress is
 *	returned in bData.
 */
void DXLQ::getByte(const byte bID[], const byte bIDLength, const byte bAddress, byte bData[])
{
	byte i;
	
	this->mParamBuffer[0] = bAddress;
	this->mParamBuffer[1] = DXL_BYTE_LENGTH;
	for (i = 0; i < bIDLength; i++) {
		bData[i] = (bID[i] <= DXL_MAX_ID && (this->isByteAddress(bID[i], bAddress))) ? this->getByteData(bID[i]) : DXL_INVALID_BYTE;
	}
}

/*
 *	For each of the bIDLength IDs in bID, the byte value parameter stored in the 
 *	corresponding bIDLength elements of the bAddress array is returned in bData.
 */
void DXLQ::getByte(const byte bID[], const byte bIDLength, const byte bAddress[], byte bData[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bData[i] = this->getByte(bID[i], bAddress[i]);
	}
}


/*
 *	Write the byte value parameter in bData to the address bAddress of all actuators.
 */
byte DXLQ::setByte(const byte bAddress, const byte bData)
{
	return this->setByte(BROADCAST_ID, bAddress, bData);
}

/*
 *	For the single ID, bID, write the byte value parameter in bData to the address
 *	bAddress. 
 */
byte DXLQ::setByte(const byte bID, const byte bAddress, const byte bData)
{
	if (this->isByteAddress(bID, bAddress)) {
		this->mParamBuffer[0] = bAddress;
		this->mParamBuffer[1] = bData;
		return this->setData(bID, INST_WRITE, 2);
	}
	return DXL_FAILURE;
}

/*
 *	For each of the bIDLength IDs in bID, the byte value parameter stored in bData is
 *	written at address bAddress. If bIDLength is greater than DXL_MAX_IDS_PER_BYTE, only
 *	data for the first DXL_MAX_IDS_PER_BYTE IDs are transmitted so as not to exceed the
 *	maximum packet length, DXL_MAX_PACKET_LENGTH bytes.
 *	http://support.robotis.com/en/product/dynamixel/communication/dxl_instruction.htm#SYNC_WRITE
 */
byte DXLQ::setByte(const byte bID[], const byte bIDLength, const byte bAddress, const byte bData)
{
	byte i, buff_idx = 1, lobyte;
	
	for (i = 0; i < bIDLength; i++) {
		if ((bIDLength > 1 && bID[i] > DXL_MAX_ID) || !(this->isByteAddress(bID[i], bAddress))) {
			return DXL_FAILURE;
		}
	}
	this->mParamBuffer[0] = bAddress;
	this->mParamBuffer[1] = DXL_BYTE_LENGTH;
	lobyte = DXL_LOBYTE(bData);
	for (i = 0; i < DXL_MIN(bIDLength, DXL_MAX_IDS_PER_BYTE); i++) {
		this->mParamBuffer[++buff_idx] = bID[i];
		this->mParamBuffer[++buff_idx] = lobyte;
	}
	return this->setData(BROADCAST_ID, INST_SYNC_WRITE, buff_idx+1);
}

/*
 *	For each of the bIDLength IDs in bID, the byte value parameters stored in the
 *	bIDLength bData array are written at address bAddress. If bIDLength is greater than
 *	DXL_MAX_IDS_PER_BYTE, only data for the first DXL_MAX_IDS_PER_BYTE IDs are transmitted
 *	so as not to exceed the maximum packet length, DXL_MAX_PACKET_LENGTH bytes.
 *	http://support.robotis.com/en/product/dynamixel/communication/dxl_instruction.htm#SYNC_WRITE
 */
byte DXLQ::setByte(const byte bID[], const byte bIDLength, const byte bAddress, const byte bData[])
{
	byte i, buff_idx = 1;
	
	for (i = 0; i < bIDLength; i++) {
		if ((bIDLength > 1 && bID[i] > DXL_MAX_ID) || !(this->isByteAddress(bID[i], bAddress))) {
			return DXL_FAILURE;
		}
	}
	this->mParamBuffer[0] = bAddress;
	this->mParamBuffer[1] = DXL_BYTE_LENGTH;
	for (i = 0; i < DXL_MIN(bIDLength, DXL_MAX_IDS_PER_BYTE); i++) {
		this->mParamBuffer[++buff_idx] = bID[i];
		this->mParamBuffer[++buff_idx] = DXL_LOBYTE(bData[i]);
	}
	return this->setData(BROADCAST_ID, INST_SYNC_WRITE, buff_idx+1);
}


/*
 *	For the single bID, the word value parameter stored at bAddress is returned.
 */
word DXLQ::getWord(const byte bID, const byte bAddress)
{
	if (bID <= DXL_MAX_ID && (this->isWordAddress(bID, bAddress))) {
		this->mParamBuffer[0] = bAddress;
		this->mParamBuffer[1] = DXL_WORD_LENGTH;
		return this->getWordData(bID);
	}
	return DXL_INVALID_WORD;
}

/*
 *	For each of the bIDLength IDs in bID, the word value parameter stored at bAddress is
 *	returned in wData.
 */
void DXLQ::getWord(const byte bID[], const byte bIDLength, const byte bAddress, word wData[])
{
	byte i;
	
	this->mParamBuffer[0] = bAddress;
	this->mParamBuffer[1] = DXL_WORD_LENGTH;
	for (i = 0; i < bIDLength; i++) {
		wData[i] = (bID[i] <= DXL_MAX_ID && (this->isWordAddress(bID[i], bAddress))) ? this->getWordData(bID[i]) : DXL_INVALID_WORD;
	}
}

/*
 *	For each of the bIDLength IDs in bID, the word value parameter stored in the 
 *	corresponding bIDLength elements of the bAddress array is returned in wData.
 */
void DXLQ::getWord(const byte bID[], const byte bIDLength, const byte bAddress[], word wData[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		wData[i] = this->getWord(bID[i], bAddress[i]);	
	}
}


/*
 *	Write the word value parameter in wData to the address bAddress of all actuators.
 */
byte DXLQ::setWord(const byte bAddress, const word wData)
{
	return this->setWord(BROADCAST_ID, bAddress, wData);
}

/*
 *	For the single ID, bID, write the word value parameter in wData to the address
 *	bAddress. 
 */
byte DXLQ::setWord(const byte bID, const byte bAddress, const word wData)
{
	if (this->isWordAddress(bID, bAddress)) {
		this->mParamBuffer[0] = bAddress;
		this->mParamBuffer[1] = DXL_LOBYTE(wData);
		this->mParamBuffer[2] = DXL_HIBYTE(wData);
		return this->setData(bID, INST_WRITE, 3);
	}
	return DXL_FAILURE;
}

/*
 *	For each of the bIDLength IDs in bID, the word value parameter stored in wData is
 *	written at address bAddress. If bIDLength is greater than DXL_MAX_IDS_PER_WORD, only
 *	data for the first DXL_MAX_IDS_PER_WORD IDs are transmitted so as not to exceed the
 *	maximum packet length, DXL_MAX_PACKET_LENGTH bytes.
 *	http://support.robotis.com/en/product/dynamixel/communication/dxl_instruction.htm#SYNC_WRITE
 */
byte DXLQ::setWord(const byte bID[], const byte bIDLength, const byte bAddress, const word wData)
{
	byte i, buff_idx = 1, lobyte, hibyte;
	
	for (i = 0; i < bIDLength; i++) {
		if ((bIDLength > 1 && bID[i] > DXL_MAX_ID) || !(this->isWordAddress(bID[i], bAddress))) {
			return DXL_FAILURE;
		}
	}
	this->mParamBuffer[0] = bAddress;
	this->mParamBuffer[1] = DXL_WORD_LENGTH;
	lobyte = DXL_LOBYTE(wData);
	hibyte = DXL_HIBYTE(wData);
	for (i = 0; i < DXL_MIN(bIDLength, DXL_MAX_IDS_PER_WORD); i++) {
		this->mParamBuffer[++buff_idx] = bID[i];
		this->mParamBuffer[++buff_idx] = lobyte;
		this->mParamBuffer[++buff_idx] = hibyte;
	}
	return this->setData(BROADCAST_ID, INST_SYNC_WRITE, buff_idx+1);
}

/*
 *	For each of the bIDLength IDs in bID, the word value parameters stored in the
 *	bIDLength wData array are written at address bAddress. If bIDLength is greater than
 *	DXL_MAX_IDS_PER_WORD, only data for the first DXL_MAX_IDS_PER_WORD IDs are transmitted
 *	so as not to exceed the maximum packet length, DXL_MAX_PACKET_LENGTH bytes.
 *	http://support.robotis.com/en/product/dynamixel/communication/dxl_instruction.htm#SYNC_WRITE
 */
byte DXLQ::setWord(const byte bID[], const byte bIDLength, const byte bAddress, const word wData[])
{
	byte i, buff_idx = 1;
	
	for (i = 0; i < bIDLength; i++) {
		if ((bIDLength > 1 && bID[i] > DXL_MAX_ID) || !(this->isWordAddress(bID[i], bAddress))) {
			return DXL_FAILURE;
		}
	}
	this->mParamBuffer[0] = bAddress;
	this->mParamBuffer[1] = DXL_WORD_LENGTH;
	for (i = 0; i < DXL_MIN(bIDLength, DXL_MAX_IDS_PER_WORD); i++) {
		this->mParamBuffer[++buff_idx] = bID[i];
		this->mParamBuffer[++buff_idx] = DXL_LOBYTE(wData[i]);
		this->mParamBuffer[++buff_idx] = DXL_HIBYTE(wData[i]);
	}
	return this->setData(BROADCAST_ID, INST_SYNC_WRITE, buff_idx+1);
}


// DXL_ID
inline byte DXLQ::isID(const byte bID)
{
	return bID == this->getByte(bID, DXL_ID);
}

void DXLQ::isID(const byte bID[], const byte bIDLength, byte bBoolean[])
{
	byte i;
	
	this->getByte(bID, bIDLength, DXL_ID, bBoolean);
	for (i = 0; i < bIDLength; i++) {
		bBoolean[i] = (bID[i] == bBoolean[i]);
	}
}


// DXL_BAUD_RATE
inline word DXLQ::getMaxBaud(const byte bID)
{
	return (this->getSeries(bID) == DXL_MX_SERIES) ? DXL_MX_MAX_BAUD : DXL_AX_MAX_BAUD;
}

void DXLQ::getMaxBaud(const byte bID[], const byte bIDLength, byte bMaxBaud[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bMaxBaud[i] = this->getMaxBaud(bID[i]);
	}
}


// DXL_LED
byte DXLQ::toggleLED(const byte bID)
{
	byte bLEDstate;
	
	bLEDstate = !(this->getByte(bID, DXL_LED));
	this->setByte(DXL_LED, bLEDstate);
	return bLEDstate;
}

void DXLQ::toggleLED(const byte bID[], const byte bIDLength)
{
	byte i, bLEDstate[bIDLength];
	
	this->getByte(bID, bIDLength, DXL_LED, bLEDstate);
	for (i = 0; i < bIDLength; i++) {
		bLEDstate[i] = !bLEDstate[i];
	}
	this->setByte(bID, bIDLength, DXL_LED, bLEDstate);
}


// DXL_GOAL_POSITION, DXL_PRESENT_POSITION
inline word DXLQ::getPositionResolution(const byte bID)
{
	return (this->getSeries(bID) == DXL_MX_SERIES) ? DXL_MX_POSITION_RESOLUTION : DXL_AX_POSITION_RESOLUTION;
}

void DXLQ::getPositionResolution(const byte bID[], const byte bIDLength, word wPositionResolution[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		wPositionResolution[i] = this->getPositionResolution(bID[i]);
	}
}


inline word DXLQ::getPosition(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_POSITION);
}

inline void DXLQ::getPosition(const byte bID[], const byte bIDLength, word wPosition[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_POSITION, wPosition);
}


// TODO: Handle BROADCAST_ID case for mixed actuator types
inline byte DXLQ::setPosition(const word wPosition)
{
	return this->setWord(DXL_GOAL_POSITION, wPosition);
}
// TODO: Handle BROADCAST_ID case for mixed actuator types
inline byte DXLQ::setPosition(const byte bID, const word wPosition)
{
	return this->setWord(bID, DXL_GOAL_POSITION, wPosition);
}

inline byte DXLQ::setPosition(const byte bID[], const byte bIDLength, const word wPosition)
{
	//byte i;
	//word wData[bIDLength];
	
	//this->getPositionResolution(bID[i]);
	return this->setWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}

inline byte DXLQ::setPosition(const byte bID[], const byte bIDLength, const word wPosition[])
{
	return this->setWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}


// DXL_MOVING_SPEED, DXL_PRESENT_SPEED
inline word DXLQ::getSpeed(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_SPEED);
}

inline void DXLQ::getSpeed(const byte bID[], const byte bIDLength, word wSpeed[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_SPEED, wSpeed);
}


inline byte DXLQ::setSpeed(const word wSpeed)
{
	return this->setWord(DXL_MOVING_SPEED, wSpeed);
}

inline byte DXLQ::setSpeed(const byte bID, const word wSpeed)
{
	return this->setWord(bID, DXL_MOVING_SPEED, wSpeed);
}

inline byte DXLQ::setSpeed(const byte bID[], const byte bIDLength, const word wSpeed)
{
	return this->setWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}

inline byte DXLQ::setSpeed(const byte bID[], const byte bIDLength, const word wSpeed[])
{
	return this->setWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}


// DXL_TORQUE_LIMIT, DXL_PRESENT_LOAD
inline word DXLQ::getLoad(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_LOAD);
}

inline void DXLQ::getLoad(const byte bID[], const byte bIDLength, word wLoad[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_LOAD, wLoad);
}


inline byte DXLQ::setLoad(const word wLoad)
{
	return this->setWord(DXL_TORQUE_LIMIT, wLoad);
}

inline byte DXLQ::setLoad(const byte bID, const word wLoad)
{
	return this->setWord(bID, DXL_TORQUE_LIMIT, wLoad);
}

inline byte DXLQ::setLoad(const byte bID[], const byte bIDLength, const word wLoad)
{
	return this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, wLoad);
}

inline byte DXLQ::setLoad(const byte bID[], const byte bIDLength, const word wLoad[])
{
	return this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, wLoad);
}


// DXL_REGISTERED
inline byte DXLQ::isRegistered(byte bID)
{
	return this->getByte(bID, DXL_REGISTERED);
}

inline void DXLQ::isRegistered(const byte bID[], const byte bIDLength, byte bRegistered[])
{
	this->getByte(bID, bIDLength, DXL_REGISTERED, bRegistered);
}


byte DXLQ::allRegistered(const byte bID[], const byte bIDLength)
{
	byte i, bRegistered[bIDLength];
	
	this->getByte(bID, bIDLength, DXL_REGISTERED, bRegistered);
	for (i = 0; i < bIDLength; i++) {
		if (bRegistered[i] == DXL_FALSE) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}

byte DXLQ::anyRegistered(const byte bID[], const byte bIDLength)
{
	byte i, bRegistered[bIDLength];
	
	this->getByte(bID, bIDLength, DXL_REGISTERED, bRegistered);
	for (i = 0; i < bIDLength; i++) {
		if (bRegistered[i] == DXL_TRUE) {
			return DXL_TRUE;
		}
	}
	return DXL_FALSE;
}


// DXL_MOVING
inline byte DXLQ::isMoving(byte bID)
{
	return this->getByte(bID, DXL_MOVING);
}

inline void DXLQ::isMoving(const byte bID[], const byte bIDLength, byte bMoving[])
{
	this->getByte(bID, bIDLength, DXL_MOVING, bMoving);
}


byte DXLQ::allMoving(const byte bID[], const byte bIDLength)
{
	byte i, bMoving[bIDLength];
	
	this->getByte(bID, bIDLength, DXL_MOVING, bMoving);
	for (i = 0; i < bIDLength; i++) {
		if (bMoving[i] == DXL_FALSE) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}

byte DXLQ::anyMoving(const byte bID[], const byte bIDLength)
{
	byte i, bMoving[bIDLength];
	
	this->getByte(bID, bIDLength, DXL_MOVING, bMoving);
	for (i = 0; i < bIDLength; i++) {
		if (bMoving[i] == DXL_TRUE) {
			return DXL_TRUE;
		}
	}
	return DXL_FALSE;
}


// DXL_JOINT_MODE
inline byte DXLQ::setJointMode(void)
{
	return this->setJointMode(BROADCAST_ID);
}

byte DXLQ::setJointMode(const byte bID)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	word wJointModeLimits[2] = {0, 0};
	
	wJointModeLimits[1] = this->getPositionResolution(bID);
	
	bStatus = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wJointModeLimits, bNumDataPerID);
	return bStatus & this->writeWord(bID, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}
// TODO: Handle broadcast ID.
byte DXLQ::setJointMode(const byte bID[], const byte bIDLength)
{
	byte bStatus;
	word wCCWAngleLimit[bIDLength];
	const word wCWAngleLimit = 0;
	
	this->getPositionResolution(bID, bIDLength, wCCWAngleLimit);
	
	bStatus = this->writeWord(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wCWAngleLimit);
	bStatus &= this->writeWord(bID, bIDLength, DXL_CCW_ANGLE_LIMIT, wCCWAngleLimit);
	return bStatus & this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}

// DXL_WHEEL_MODE
inline byte DXLQ::setWheelMode(void)
{
	return this->setWheelMode(BROADCAST_ID);
}

byte DXLQ::setWheelMode(const byte bID)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	const word  wWheelModeLimits[2] = {0, 0};
	
	bStatus = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID);
	return bStatus & this->writeWord(bID, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}
// TODO: Handle broadcast ID.
byte DXLQ::setWheelMode(const byte bID[], const byte bIDLength)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	const word wWheelModeLimits[2] = {0, 0};
	
	bStatus = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID, bNumDataPerID);
	return bStatus & this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}

// DXL_MULTI_TURN_MODE
inline byte DXLQ::setMultiTurnMode(void)
{
	return this->setMultiTurnMode(BROADCAST_ID);
}
// TODO: Handle broadcast ID.
byte DXLQ::setMultiTurnMode(const byte bID)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	const word wMultiTurnModeLimits[2] = {DXL_MX_POSITION_RESOLUTION, DXL_MX_POSITION_RESOLUTION}, wMultiTurnOffset = 0;
	
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		bStatus = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wMultiTurnModeLimits, bNumDataPerID);
		bStatus &= this->writeWord(bID, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
		return bStatus & this->writeWord(bID, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
	}
	return DXL_FAILURE;
}

byte DXLQ::setMultiTurnMode(const byte bID[], const byte bIDLength)
{
	byte i, bStatus;
	const word wMultiTurnOffset = 0;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
	}
	bStatus = this->writeWord(bID, bIDLength, DXL_CW_ANGLE_LIMIT, DXL_MX_POSITION_RESOLUTION);
	bStatus &= this->writeWord(bID, bIDLength, DXL_CCW_ANGLE_LIMIT, DXL_MX_POSITION_RESOLUTION);
	bStatus &= this->writeWord(bID, bIDLength, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
	return bStatus & this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}

// DXL_TORQUE_CONTROL_MODE
inline byte DXLQ::setTorqueControlMode(void)
{
	return this->setTorqueControlMode(BROADCAST_ID);
}
// TODO: Handle broadcast ID.
byte DXLQ::setTorqueControlMode(const byte bID)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	const word  wWheelModeLimits[2] = {0, 0};
	
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		bStatus = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID);
		bStatus &= this->writeWord(bID, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
		return bStatus & this->writeByte(bID, DXL_TORQUE_CONTROL_MODE_ENABLE, DXL_TRUE);
	}
	return DXL_FAILURE;
}

byte DXLQ::setTorqueControlMode(const byte bID[], const byte bIDLength)
{
	byte i, bStatus;
	const byte bNumDataPerID = 2;
	const word wWheelModeLimits[2] = {0, 0};
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
	}
	bStatus = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID, bNumDataPerID);
	bStatus &= this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
	return bStatus & this->writeByte(bID, bIDLength, DXL_TORQUE_CONTROL_MODE_ENABLE, DXL_TRUE);
}


inline byte DXLQ::getMode(const byte bID)
{
	byte bTorqueControlMode;
	word wCWAngleLimit, wCCWAngleLimit;
	
	if (bID <= DXL_MAX_ID) {
		bTorqueControlMode = this->getByte(bID, DXL_TORQUE_CONTROL_MODE_ENABLE);
		if (bTorqueControlMode == DXL_TRUE) {
			return DXL_TORQUE_CONTROL_MODE;
		} else if (bTorqueControlMode == DXL_FALSE) {
			wCWAngleLimit = this->getWord(bID, DXL_CW_ANGLE_LIMIT);
			if (wCWAngleLimit == 0) {
				wCCWAngleLimit = this->getWord(bID, DXL_CCW_ANGLE_LIMIT);
				if (wCWAngleLimit == 0) {
					return DXL_WHEEL_MODE;
				} else if (wCCWAngleLimit != DXL_INVALID_WORD) {
					return DXL_JOINT_MODE;
				}
			} else if (wCWAngleLimit != DXL_INVALID_WORD) {
				return DXL_MULTI_TURN_MODE;
			}
		}
	}
	return DXL_UNKNOWN_MODE;
}

void DXLQ::getMode(const byte bID[], const byte bIDLength, byte bMode[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bMode[i] = this->getMode(bID[i]);
	}
}


inline byte DXLQ::zeroSpeed(void)
{
	return this->zeroSpeed(BROADCAST_ID);
}


inline byte DXLQ::zeroSpeed(const byte bID)
{
	//const byte bNumDataPerID = 2;
	//const word wSpeedTorque[2] = {0, 0};
	const word wSpeed = 0;
	
	//return this->syncWrite(bID, DXL_MOVING_SPEED, wSpeedTorque, bNumDataPerID);
	return this->setWord(bID, DXL_MOVING_SPEED, wSpeed);
}

inline byte DXLQ::zeroSpeed(const byte bID[], const byte bIDLength)
{
	//const byte bNumDataPerID = 2;
	//const word wSpeedTorque[2] = {0, 0};
	const word wSpeed = 0;
	
	//return this->syncWrite(bID, bIDLength, DXL_MOVING_SPEED, wSpeedTorque, bNumDataPerID, bNumDataPerID);
	return this->setWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}

#endif /* DXL_UTILS_H_ */