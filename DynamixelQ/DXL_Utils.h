/*
 *	DXL_Utils.h
 *	
 *	Author: Andrew D. Horchler, horchler @ gmail . com
 *	Created: 2-23-15, modified: 7-30-15
 */
 
#ifndef DXL_UTILS_H_
#define DXL_UTILS_H_

#include "DXL_Validate.h"

#define DXL_UTILS_RETRY_NSDELAY 1L

static int DXL_UTILS_RETRY_COUNT = 0;


inline int DXL::getRetryCount(void)
{
	return DXL_UTILS_RETRY_COUNT;
}

inline void DXL::setRetryCount(int retryCount)
{
	DXL_UTILS_RETRY_COUNT = retryCount;
}


inline void DXL::fillByteArray(byte bArray[], const byte bArrayLength, const byte bValue)
{
	byte i;
	
	for (i = 0; i < bArrayLength; i++) {
		bArray[i] = bValue;
	} 
}

inline void DXL::fillWordArray(word wArray[], const byte bArrayLength, const word wValue)
{
	byte i;
	
	for (i = 0; i < bArrayLength; i++) {
		wArray[i] = wValue;
	} 
}


inline byte DXL::doPing(const byte bID)
{
	int retryCount = 0;
	byte bStatus;
	
	if (this->isValidActuatorID(bID)) {
		bStatus = this->txRxPacket(bID, INST_PING, 0);
		while (retryCount < DXL_UTILS_RETRY_COUNT && !bStatus) {
			nsDelay(DXL_UTILS_RETRY_NSDELAY);
			bStatus = this->txRxPacket(bID, INST_PING, 0);
			retryCount++;
		}
		return bStatus ? this->mRxBuffer[2] : DXL_INVALID_BYTE;
	}
	return DXL_INVALID_BYTE;
}

void DXL::doPing(const byte bID[], const byte bIDLength, byte bPingID[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bPingID[i] = this->doPing(bID[i]);
	}
}


byte DXL::getByteData(const byte bID)
{
	int retryCount = 0;
	byte bStatus;
	
	if (this->isValidActuatorID(bID)) {
		bStatus = this->txRxPacket(bID, INST_READ, 2);
		while (retryCount < DXL_UTILS_RETRY_COUNT && !bStatus) {
			nsDelay(DXL_UTILS_RETRY_NSDELAY);
			bStatus = this->txRxPacket(bID, INST_READ, 2);
			retryCount++;
		}
		return bStatus ? this->mRxBuffer[5] : DXL_INVALID_BYTE;
	}
	return DXL_INVALID_BYTE;
}

word DXL::getWordData(const byte bID)
{
	int retryCount = 0;
	byte bStatus;
	
	if (this->isValidActuatorID(bID)) {
		bStatus = this->txRxPacket(bID, INST_READ, 2);
		while (retryCount < DXL_UTILS_RETRY_COUNT && !bStatus) {
			nsDelay(DXL_UTILS_RETRY_NSDELAY);
			bStatus = this->txRxPacket(bID, INST_READ, 2);
			retryCount++;
		}
		return bStatus ? DXL_MAKEWORD(this->mRxBuffer[5], this->mRxBuffer[6]) : DXL_INVALID_WORD;
	}
	return DXL_INVALID_WORD;
}


DXL_RETURN_TYPE DXL::setData(const byte bID, const DXL_INSTRUCTION bInstruction, const byte bParamLen)
{
	int retryCount = 0;
	byte bStatus;
	
	bStatus = this->txRxPacket(bID, bInstruction, bParamLen);
	while (retryCount < DXL_UTILS_RETRY_COUNT && !bStatus) {
		nsDelay(DXL_UTILS_RETRY_NSDELAY);
		bStatus = this->txRxPacket(bID, bInstruction, bParamLen);
		retryCount++;
	}
	return (bStatus == 1) ? DXL_SUCCESS : DXL_FAILURE;
}


/*
 *	For the single bID, the byte value parameter stored at bAddress is returned.
 */
byte DXL::getByte(const byte bID, const byte bAddress)
{
	if (this->isValidActuatorID(bID) && this->isByteAddress(bID, bAddress)) {
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
void DXL::getByte(const byte bID[], const byte bIDLength, const byte bAddress, byte bData[])
{
	byte i;
	
	this->mParamBuffer[0] = bAddress;
	this->mParamBuffer[1] = DXL_BYTE_LENGTH;
	for (i = 0; i < bIDLength; i++) {
		bData[i] = (this->isValidActuatorID(bID[i]) && this->isByteAddress(bID[i], bAddress)) ? this->getByteData(bID[i]) : DXL_INVALID_BYTE;
	}
}

/*
 *	For each of the bIDLength IDs in bID, the byte value parameter stored in the 
 *	corresponding bIDLength elements of the bAddress array is returned in bData.
 */
void DXL::getByte(const byte bID[], const byte bIDLength, const byte bAddress[], byte bData[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bData[i] = this->getByte(bID[i], bAddress[i]);
	}
}


/*
 *	Write the byte value parameter in bData to the address bAddress of all actuators.
 */
byte DXL::setByte(const byte bAddress, const byte bData)
{
	return this->setByte(BROADCAST_ID, bAddress, bData);
}

/*
 *	For the single ID, bID, write the byte value parameter in bData to the address
 *	bAddress. 
 */
byte DXL::setByte(const byte bID, const byte bAddress, const byte bData)
{
	if (this->isValidID(bID) && this->isByteAddress(bID, bAddress)) {
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
byte DXL::setByte(const byte bID[], const byte bIDLength, const byte bAddress, const byte bData)
{
	byte i, buff_idx = 1, lobyte;
	
	if (bIDLength > 1) {
		for (i = 0; i < bIDLength; i++) {
			if (!(this->isValidID(bID[i])) || !(this->isByteAddress(bID[i], bAddress))) {
				return DXL_FAILURE;
			}
		}
	} else {
		return (bIDLength == 1) ? this->setByte(bID[0], bAddress, bData) : DXL_FAILURE;
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
byte DXL::setByte(const byte bID[], const byte bIDLength, const byte bAddress, const byte bData[])
{
	byte i, buff_idx = 1;
	
	if (bIDLength > 1) {
		for (i = 0; i < bIDLength; i++) {
			if (!(this->isValidID(bID[i])) || !(this->isByteAddress(bID[i], bAddress))) {
				return DXL_FAILURE;
			}
		}
	} else {
		return (bIDLength == 1) ? this->setByte(bID[0], bAddress, bData[0]) : DXL_FAILURE;
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
word DXL::getWord(const byte bID, const byte bAddress)
{
	if (this->isValidActuatorID(bID) && this->isWordAddress(bID, bAddress)) {
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
void DXL::getWord(const byte bID[], const byte bIDLength, const byte bAddress, word wData[])
{
	byte i;
	
	this->mParamBuffer[0] = bAddress;
	this->mParamBuffer[1] = DXL_WORD_LENGTH;
	for (i = 0; i < bIDLength; i++) {
		wData[i] = (this->isValidActuatorID(bID[i]) && this->isWordAddress(bID[i], bAddress)) ? this->getWordData(bID[i]) : DXL_INVALID_WORD;
	}
}

/*
 *	For each of the bIDLength IDs in bID, the word value parameter stored in the 
 *	corresponding bIDLength elements of the bAddress array is returned in wData.
 */
void DXL::getWord(const byte bID[], const byte bIDLength, const byte bAddress[], word wData[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		wData[i] = this->getWord(bID[i], bAddress[i]);	
	}
}


/*
 *	Write the word value parameter in wData to the address bAddress of all actuators.
 */
byte DXL::setWord(const byte bAddress, const word wData)
{
	return this->setWord(BROADCAST_ID, bAddress, wData);
}

/*
 *	For the single ID, bID, write the word value parameter in wData to the address
 *	bAddress. 
 */
byte DXL::setWord(const byte bID, const byte bAddress, const word wData)
{
	if (this->isValidID(bID) && this->isWordAddress(bID, bAddress)) {
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
byte DXL::setWord(const byte bID[], const byte bIDLength, const byte bAddress, const word wData)
{
	byte i, buff_idx = 1, lobyte, hibyte;
	
	if (bIDLength > 1) {
		for (i = 0; i < bIDLength; i++) {
			if (!(this->isValidID(bID[i])) || !(this->isWordAddress(bID[i], bAddress))) {
				return DXL_FAILURE;
			}
		}
	} else {
		return (bIDLength == 1) ? this->setWord(bID[0], bAddress, wData) : DXL_FAILURE;
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
byte DXL::setWord(const byte bID[], const byte bIDLength, const byte bAddress, const word wData[])
{
	byte i, buff_idx = 1;
	
	if (bIDLength > 1) {
		for (i = 0; i < bIDLength; i++) {
			if (!(this->isValidID(bID[i])) || !(this->isWordAddress(bID[i], bAddress))) {
				return DXL_FAILURE;
			}
		}
	} else {
		return (bIDLength == 1) ? this->setWord(bID[0], bAddress, wData[0]) : DXL_FAILURE;
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
inline byte DXL::isID(const byte bID)
{
	return bID == this->getByte(bID, DXL_ID);
}

void DXL::isID(const byte bID[], const byte bIDLength, byte bIsID[])
{
	byte i;
	
	this->getByte(bID, bIDLength, DXL_ID, bIsID);
	for (i = 0; i < bIDLength; i++) {
		bIsID[i] = (bID[i] == bIsID[i]);
	}
}


// DXL_BAUD_RATE
inline word DXL::getMaxBaud(const byte bID)
{
	return (this->getSeries(bID) == DXL_MX_SERIES) ? DXL_MX_MAX_BAUD_RATE_VALUE : DXL_AX_MAX_BAUD_RATE_VALUE;
}

void DXL::getMaxBaud(const byte bID[], const byte bIDLength, byte bMaxBaud[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bMaxBaud[i] = this->getMaxBaud(bID[i]);
	}
}


// DXL_LED
byte DXL::toggleLED(const byte bID)
{
	byte bLEDstate;
	
	bLEDstate = this->getByte(bID, DXL_LED);
	if (bLEDstate != DXL_INVALID_BYTE) {
		bLEDstate = !bLEDstate;
		this->setByte(DXL_LED, bLEDstate);
	}
	return bLEDstate;
}

void DXL::toggleLED(const byte bID[], byte bIDLength)
{
	byte i, bLEDstate[bIDLength], bOffset = 0;
	
	this->getByte(bID, bIDLength, DXL_LED, bLEDstate);
	for (i = 0; i < bIDLength; i++) {
		if (bLEDstate[i] == DXL_INVALID_BYTE) {
		    bOffset++;
			bIDLength--;
		} else {
			bLEDstate[i-bOffset] = !bLEDstate[i];
		}
	}
	this->setByte(bID, bIDLength, DXL_LED, bLEDstate);
}


// DXL_GOAL_POSITION, DXL_PRESENT_POSITION
inline word DXL::getPositionResolution(const byte bID)
{
	return (this->getSeries(bID) == DXL_MX_SERIES) ? DXL_MX_POSITION_RESOLUTION : DXL_AX_POSITION_RESOLUTION;
}

void DXL::getPositionResolution(const byte bID[], const byte bIDLength, word wPositionResolution[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		wPositionResolution[i] = this->getPositionResolution(bID[i]);
	}
}


inline word DXL::getPosition(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_POSITION);
}

inline void DXL::getPosition(const byte bID[], const byte bIDLength, word wPosition[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_POSITION, wPosition);
}


// TODO: Handle BROADCAST_ID case for mixed actuator types
inline byte DXL::setPosition(const word wPosition)
{
	return this->setWord(DXL_GOAL_POSITION, wPosition);
}
// TODO: Handle BROADCAST_ID case for mixed actuator types
inline byte DXL::setPosition(const byte bID, const word wPosition)
{
	return this->setWord(bID, DXL_GOAL_POSITION, wPosition);
}

inline byte DXL::setPosition(const byte bID[], const byte bIDLength, const word wPosition)
{
	//byte i;
	//word wData[bIDLength];
	
	//this->getPositionResolution(bID[i]);
	return this->setWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}

inline byte DXL::setPosition(const byte bID[], const byte bIDLength, const word wPosition[])
{
	return this->setWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}


// DXL_MOVING_SPEED, DXL_PRESENT_SPEED
inline word DXL::getSpeed(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_SPEED);
}

inline void DXL::getSpeed(const byte bID[], const byte bIDLength, word wSpeed[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_SPEED, wSpeed);
}


inline byte DXL::setSpeed(const word wSpeed)
{
	return this->setWord(DXL_MOVING_SPEED, wSpeed);
}

inline byte DXL::setSpeed(const byte bID, const word wSpeed)
{
	return this->setWord(bID, DXL_MOVING_SPEED, wSpeed);
}

inline byte DXL::setSpeed(const byte bID[], const byte bIDLength, const word wSpeed)
{
	return this->setWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}

inline byte DXL::setSpeed(const byte bID[], const byte bIDLength, const word wSpeed[])
{
	return this->setWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}


// DXL_TORQUE_LIMIT, DXL_PRESENT_LOAD
inline word DXL::getLoad(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_LOAD);
}

inline void DXL::getLoad(const byte bID[], const byte bIDLength, word wLoad[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_LOAD, wLoad);
}


inline byte DXL::setLoad(const word wLoad)
{
	return this->setWord(DXL_TORQUE_LIMIT, wLoad);
}

inline byte DXL::setLoad(const byte bID, const word wLoad)
{
	return this->setWord(bID, DXL_TORQUE_LIMIT, wLoad);
}

inline byte DXL::setLoad(const byte bID[], const byte bIDLength, const word wLoad)
{
	return this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, wLoad);
}

inline byte DXL::setLoad(const byte bID[], const byte bIDLength, const word wLoad[])
{
	return this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, wLoad);
}


// DXL_REGISTERED
inline byte DXL::isRegistered(byte bID)
{
	return this->getByte(bID, DXL_REGISTERED);
}

inline void DXL::isRegistered(const byte bID[], const byte bIDLength, byte bRegistered[])
{
	this->getByte(bID, bIDLength, DXL_REGISTERED, bRegistered);
}


byte DXL::allRegistered(const byte bID[], const byte bIDLength)
{
	byte i, bRegistered[bIDLength];
	
	this->getByte(bID, bIDLength, DXL_REGISTERED, bRegistered);
	for (i = 0; i < bIDLength; i++) {
		if (bRegistered[i] != DXL_TRUE) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}

byte DXL::anyRegistered(const byte bID[], const byte bIDLength)
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
inline byte DXL::isMoving(byte bID)
{
	return this->getByte(bID, DXL_MOVING);
}

inline void DXL::isMoving(const byte bID[], const byte bIDLength, byte bMoving[])
{
	this->getByte(bID, bIDLength, DXL_MOVING, bMoving);
}


byte DXL::allMoving(const byte bID[], const byte bIDLength)
{
	byte i, bMoving[bIDLength];
	
	this->getByte(bID, bIDLength, DXL_MOVING, bMoving);
	for (i = 0; i < bIDLength; i++) {
		if (bMoving[i] != DXL_TRUE) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}

byte DXL::anyMoving(const byte bID[], const byte bIDLength)
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
inline byte DXL::setJointMode(void)
{
	return this->setJointMode(BROADCAST_ID);
}

byte DXL::setJointMode(const byte bID)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	word wJointModeLimits[2] = {0, 0};
	
	wJointModeLimits[1] = this->getPositionResolution(bID);
	
	bStatus = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wJointModeLimits, bNumDataPerID);
	return bStatus & this->setWord(bID, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}
// TODO: Handle broadcast ID.
byte DXL::setJointMode(const byte bID[], const byte bIDLength)
{
	byte bStatus;
	word wCCWAngleLimit[bIDLength];
	const word wCWAngleLimit = 0;
	
	this->getPositionResolution(bID, bIDLength, wCCWAngleLimit);
	
	bStatus = this->setWord(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wCWAngleLimit);
	bStatus &= this->setWord(bID, bIDLength, DXL_CCW_ANGLE_LIMIT, wCCWAngleLimit);
	return bStatus & this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}

inline byte DXL::isJointMode(const byte bID)
{
	return (this->getMode(bID) == DXL_JOINT_MODE);
}

void DXL::isJointMode(const byte bID[], const byte bIDLength, byte bIsJointMode[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bIsJointMode[i] = this->isJointMode(bID[i]);
	}
}

// DXL_WHEEL_MODE
inline byte DXL::setWheelMode(void)
{
	return this->setWheelMode(BROADCAST_ID);
}

byte DXL::setWheelMode(const byte bID)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	const word  wWheelModeLimits[2] = {0, 0};
	
	bStatus = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID);
	return bStatus & this->setWord(bID, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}

byte DXL::setWheelMode(const byte bID[], const byte bIDLength)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	const word wWheelModeLimits[2] = {0, 0};
	
	if (bIDLength > 1 && !(this->allValidID(bID, bIDLength))) {
		return DXL_FAILURE;
	} else {
		return (bIDLength == 1) ? this->setWheelMode(bID[0]) : DXL_FAILURE;
	}
	bStatus = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID, bNumDataPerID);
	return bStatus & this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}

inline byte DXL::isWheelMode(const byte bID)
{
	return (this->getMode(bID) == DXL_WHEEL_MODE);
}

void DXL::isWheelMode(const byte bID[], const byte bIDLength, byte bIsWheelMode[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bIsWheelMode[i] = this->isWheelMode(bID[i]);
	}
}

// DXL_MULTI_TURN_MODE
inline byte DXL::setMultiTurnMode(void)
{
	return this->setMultiTurnMode(BROADCAST_ID);
}

byte DXL::setMultiTurnMode(const byte bID)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	const word wMultiTurnModeLimits[2] = {DXL_MX_POSITION_RESOLUTION, DXL_MX_POSITION_RESOLUTION}, wMultiTurnOffset = 0;
	
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		bStatus = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wMultiTurnModeLimits, bNumDataPerID);
		bStatus &= this->setWord(bID, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
		return bStatus & this->setWord(bID, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
	}
	return DXL_FAILURE;
}

byte DXL::setMultiTurnMode(const byte bID[], const byte bIDLength)
{
	byte i, bStatus;
	const word wMultiTurnOffset = 0;
	
	if (bIDLength > 1) {
		if (!(this->allValidID(bID, bIDLength))) {
			return DXL_FAILURE;
		} else {
			for (i = 0; i < bIDLength; i++) {
				if (this->getSeries(bID[i]) != DXL_MX_SERIES) {
					return DXL_FAILURE;
				}
			}
		}
	} else {
		return (bIDLength == 1) ? this->setMultiTurnMode(bID[0]) : DXL_FAILURE;
	}
	bStatus = this->setWord(bID, bIDLength, DXL_CW_ANGLE_LIMIT, DXL_MX_POSITION_RESOLUTION);
	bStatus &= this->setWord(bID, bIDLength, DXL_CCW_ANGLE_LIMIT, DXL_MX_POSITION_RESOLUTION);
	bStatus &= this->setWord(bID, bIDLength, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
	return bStatus & this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
}

inline byte DXL::isMultiTurnMode(const byte bID)
{
	return (this->getMode(bID) == DXL_MULTI_TURN_MODE);
}

void DXL::isMultiTurnMode(const byte bID[], const byte bIDLength, byte bIsMultiTurnMode[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bIsMultiTurnMode[i] = this->isMultiTurnMode(bID[i]);
	}
}

// DXL_TORQUE_CONTROL_MODE
inline byte DXL::setTorqueControlMode(void)
{
	return this->setTorqueControlMode(BROADCAST_ID);
}

byte DXL::setTorqueControlMode(const byte bID)
{
	byte bStatus;
	const byte bNumDataPerID = 2;
	const word  wWheelModeLimits[2] = {0, 0};
	
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		bStatus = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID);
		bStatus &= this->setWord(bID, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
		return bStatus & this->setWord(bID, DXL_TORQUE_CONTROL_MODE_ENABLE, DXL_TRUE);
	}
	return DXL_FAILURE;
}

byte DXL::setTorqueControlMode(const byte bID[], const byte bIDLength)
{
	byte i, bStatus;
	const byte bNumDataPerID = 2;
	const word wWheelModeLimits[2] = {0, 0};
	
	if (bIDLength > 1) {
		if (!(this->allValidID(bID, bIDLength))) {
			return DXL_FAILURE;
		} else {
			for (i = 0; i < bIDLength; i++) {
				if (this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
					return DXL_FAILURE;
				}
			}
		}
	} else {
		return (bIDLength == 1) ? this->setTorqueControlMode(bID[0]) : DXL_FAILURE;
	}
	bStatus = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID, bNumDataPerID);
	bStatus &= this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, DXL_MAX_TORQUE_LIMIT);
	return bStatus & this->setWord(bID, bIDLength, DXL_TORQUE_CONTROL_MODE_ENABLE, DXL_TRUE);
}

inline byte DXL::isTorqueControlMode(const byte bID)
{
	return (this->getMode(bID) == DXL_TORQUE_CONTROL_MODE);
}

void DXL::isTorqueControlMode(const byte bID[], const byte bIDLength, byte bIsTorqueControlMode[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bIsTorqueControlMode[i] = this->isTorqueControlMode(bID[i]);
	}
}


inline byte DXL::getMode(const byte bID)
{
	byte bTorqueControlMode;
	word wCWAngleLimit, wCCWAngleLimit;
	
	if (this->isValidActuatorID(bID)) {
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

void DXL::getMode(const byte bID[], const byte bIDLength, byte bMode[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bMode[i] = this->getMode(bID[i]);
	}
}

inline byte DXL::setMode(const byte bMode)
{
	return this->setMode(BROADCAST_ID, bMode);
}

inline byte DXL::setMode(const byte bID, const byte bMode)
{
	switch(bID){
		case DXL_JOINT_MODE:
			return this->setJointMode(bID);
		case DXL_WHEEL_MODE:
			return this->setWheelMode(bID);
		case DXL_MULTI_TURN_MODE:
			return this->setMultiTurnMode(bID);
		case DXL_TORQUE_CONTROL_MODE:
			return this->setTorqueControlMode(bID);
		default:
			return DXL_FAILURE;
	}
}

void DXL::setMode(const byte bID[], const byte bIDLength, const byte bMode[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		this->setMode(bID[i], bMode[i]);
	}
}

inline byte DXL::isMode(const byte bID, const byte bMode)
{
	return (this->getMode(bID) == bMode);
}

void DXL::isMode(const byte bID[], byte bIDLength, const byte bMode[], byte bIsMode[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bIsMode[i] = this->isMode(bID[i], bMode[i]);
	}
}


// DXL_GOAL_POSITION
inline word DXL::zero(const byte bID)
{
	word wPosition;
	
	wPosition = this->getWord(bID, DXL_PRESENT_POSITION);
	return (wPosition != DXL_INVALID_WORD && this->setWord(bID, DXL_GOAL_POSITION, wPosition) == DXL_SUCCESS) ? wPosition : DXL_INVALID_WORD;
}

inline byte DXL::zero(const byte bID[], const byte bIDLength, word wPosition[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_POSITION, wPosition);
	return this->setWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}


// DXL_MOVING_SPEED
inline byte DXL::stop(void)
{
	return this->stop(BROADCAST_ID);
}


inline byte DXL::stop(const byte bID)
{
	const word wSpeed = 0;
	
	return this->setWord(bID, DXL_MOVING_SPEED, wSpeed);
}

inline byte DXL::stop(const byte bID[], const byte bIDLength)
{
	const word wSpeed = 0;
	
	return this->setWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}

#endif /* DXL_UTILS_H_ */