/*
 *	DXL_Utils.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 2-23-15, modified: 3-22-15
 */
 
#ifndef DXL_UTILS_H
#define DXL_UTILS_H

#include "DynamixelQ.h"

// DXL_MODEL_NUMBER
inline word DynamixelQ::getModel(const byte bID)
{
	return this->readWord(bID, DXL_MODEL_NUMBER);
}

inline void DynamixelQ::getModel(const byte bID[], const byte bIDLength, word wModelNumber[])
{
	this->readWord(bID, bIDLength, DXL_MODEL_NUMBER, wModelNumber);
}


// DXL_VERSION_OF_FIRMWARE
inline byte DynamixelQ::getFirmware(const byte bID)
{
	return this->readByte(bID, DXL_VERSION_OF_FIRMWARE);
}

inline void DynamixelQ::getFirmware(const byte bID[], const byte bIDLength, byte bFirmwareVersion[])
{
	this->readByte(bID, bIDLength, DXL_VERSION_OF_FIRMWARE, bFirmwareVersion);
}


// DXL_ID
inline byte DynamixelQ::isID(const byte bID)
{
	return bID == this->readByte(bID, DXL_ID);
}

byte DynamixelQ::isID(const byte bID[], const byte bIDLength)
{
	byte i, bBoolean[bIDLength];
	
	this->readByte(bID, bIDLength, DXL_ID, bBoolean);
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] != bBoolean[i]) {
			return 0;
		}
	}
	return 1;
}

void DynamixelQ::isID(const byte bID[], const byte bIDLength, byte bBoolean[])
{
	byte i;
	
	this->readByte(bID, bIDLength, DXL_ID, bBoolean);
	for (i = 0; i < bIDLength; i++) {
		bBoolean[i] = (bID[i] == bBoolean[i]);
	}
}


// DXL_BAUD_RATE
inline byte DynamixelQ::getBaudRate(const byte bID)
{
	return this->readByte(bID, DXL_BAUD_RATE);
}

inline void DynamixelQ::getBaudRate(const byte bID[], const byte bIDLength, byte bBaudRate[])
{
	this->readByte(bID, bIDLength, DXL_BAUD_RATE, bBaudRate);
}


// DXL_RETURN_DELAY_TIME
inline byte DynamixelQ::getReturnDelay(const byte bID)
{
	return this->readByte(bID, DXL_RETURN_DELAY_TIME);
}

inline void DynamixelQ::getReturnDelay(const byte bID[], const byte bIDLength, byte bReturnDelay[])
{
	this->readByte(bID, bIDLength, DXL_RETURN_DELAY_TIME, bReturnDelay);
}

inline byte DynamixelQ::setReturnDelay(const byte bReturnDelay)
{
	return this->writeByte(DXL_RETURN_DELAY_TIME, bReturnDelay & DXL_MAX_RETURN_DELAY_TIME);
}

inline byte DynamixelQ::setReturnDelay(const byte bID, const byte bReturnDelay)
{
	return this->writeByte(bID, DXL_RETURN_DELAY_TIME, bReturnDelay & DXL_MAX_RETURN_DELAY_TIME);
}

inline byte DynamixelQ::setReturnDelay(const byte bID[], const byte bIDLength, const byte bReturnDelay)
{
	return this->writeByte(bID, bIDLength, DXL_RETURN_DELAY_TIME, bReturnDelay & DXL_MAX_RETURN_DELAY_TIME);
}

byte DynamixelQ::setReturnDelay(const byte bID[], const byte bIDLength, byte bReturnDelay[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bReturnDelay[i] &= DXL_MAX_RETURN_DELAY_TIME;
	}
	return this->writeByte(bID, bIDLength, DXL_RETURN_DELAY_TIME, bReturnDelay);
}


// DXL_LED
inline byte DynamixelQ::getLED(const byte bID)
{
	return this->readByte(bID, DXL_LED);
}
	
inline void DynamixelQ::getLED(const byte bID[], const byte bIDLength, byte bLEDstate[])
{
	this->readByte(bID, bIDLength, DXL_LED, bLEDstate);
}

inline byte DynamixelQ::setLED(const byte bLEDstate)
{
	return this->writeByte(DXL_LED, bLEDstate);
}

inline byte DynamixelQ::setLED(const byte bID, const byte bLEDstate)
{
	return this->writeByte(bID, DXL_LED, bLEDstate);
}

inline byte DynamixelQ::setLED(const byte bID[], const byte bIDLength, const byte bLEDstate)
{
	return this->writeByte(bID, bIDLength, DXL_LED, bLEDstate);
}

inline byte DynamixelQ::setLED(const byte bID[], const byte bIDLength, const byte bLEDstate[])
{
	return this->writeByte(bID, bIDLength, DXL_LED, bLEDstate);
}


// DXL_GOAL_POSITION, DXL_PRESENT_POSITION
inline word DynamixelQ::getPosition(const byte bID)
{
	return this->readWord(bID, DXL_PRESENT_POSITION);
}

inline void DynamixelQ::getPosition(const byte bID[], const byte bIDLength, word wPosition[])
{
	this->readWord(bID, bIDLength, DXL_PRESENT_POSITION, wPosition);
}


inline byte DynamixelQ::setPosition(const word wPosition)
{
	return this->writeWord(DXL_GOAL_POSITION, wPosition);
}

inline byte DynamixelQ::setPosition(const byte bID, const word wPosition)
{
	return this->writeWord(bID, DXL_GOAL_POSITION, wPosition);
}

inline byte DynamixelQ::setPosition(const byte bID[], const byte bIDLength, const word wPosition)
{
	return this->writeWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}

inline byte DynamixelQ::setPosition(const byte bID[], const byte bIDLength, const word wPosition[])
{
	return this->writeWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}


// DXL_MOVING_SPEED, DXL_PRESENT_SPEED
inline word DynamixelQ::getSpeed(const byte bID)
{
	return this->readWord(bID, DXL_PRESENT_SPEED);
}

inline void DynamixelQ::getSpeed(const byte bID[], const byte bIDLength, word wSpeed[])
{
	this->readWord(bID, bIDLength, DXL_PRESENT_SPEED, wSpeed);
}


inline byte DynamixelQ::setSpeed(const word wSpeed)
{
	return this->writeWord(DXL_MOVING_SPEED, wSpeed);
}

inline byte DynamixelQ::setSpeed(const byte bID, const word wSpeed)
{
	return this->writeWord(bID, DXL_MOVING_SPEED, wSpeed);
}

inline byte DynamixelQ::setSpeed(const byte bID[], const byte bIDLength, const word wSpeed)
{
	return this->writeWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}

inline byte DynamixelQ::setSpeed(const byte bID[], const byte bIDLength, const word wSpeed[])
{
	return this->writeWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}


// DXL_TORQUE_LIMIT, DXL_PRESENT_LOAD
inline word DynamixelQ::getLoad(const byte bID)
{
	return this->readWord(bID, DXL_PRESENT_LOAD);
}

inline void DynamixelQ::getLoad(const byte bID[], const byte bIDLength, word wLoad[])
{
	this->readWord(bID, bIDLength, DXL_PRESENT_LOAD, wLoad);
}


inline byte DynamixelQ::setLoad(const word wLoad)
{
	return this->writeWord(DXL_TORQUE_LIMIT, wLoad);
}

inline byte DynamixelQ::setLoad(const byte bID, const word wLoad)
{
	return this->writeWord(bID, DXL_TORQUE_LIMIT, wLoad);
}

inline byte DynamixelQ::setLoad(const byte bID[], const byte bIDLength, const word wLoad)
{
	return this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, wLoad);
}

inline byte DynamixelQ::setLoad(const byte bID[], const byte bIDLength, const word wLoad[])
{
	return this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, wLoad);
}

// DXL_MOVING
inline byte DynamixelQ::isMoving(byte bID)
{
	return this->readByte(bID, DXL_MOVING);
}

byte DynamixelQ::isMoving(const byte bID[], const byte bIDLength)
{
	byte i, bBoolean[bIDLength];
	
	this->readByte(bID, bIDLength, DXL_MOVING, bBoolean);
	for (i = 0; i < bIDLength; i++) {
		if (bBoolean[i] == (byte)1) {
			return 1;
		}
	}
	return 0;
}

inline void DynamixelQ::isMoving(const byte bID[], const byte bIDLength, byte bBoolean[])
{
	this->readByte(bID, bIDLength, DXL_MOVING, bBoolean);
}


// DXL_CW_ANGLE_LIMIT, DXL_CCW_ANGLE_LIMIT
inline byte DynamixelQ::setJointMode(void)
{
	return this->setJointMode(BROADCAST_ID);
}

byte DynamixelQ::setJointMode(const byte bID)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wJointModeLimits[2] = {0, DXL_POSITION_RESOLUTION}, wTorqueLimit = DXL_MAX_TORQUE_LIMIT;
	
	status = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wJointModeLimits, bNumDataPerID);
	return status & this->writeWord(bID, DXL_TORQUE_LIMIT, wTorqueLimit);
}

byte DynamixelQ::setJointMode(const byte bID[], const byte bIDLength)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wJointModeLimits[2] = {0, DXL_POSITION_RESOLUTION}, wTorqueLimit = DXL_MAX_TORQUE_LIMIT;
	
	status = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wJointModeLimits, bNumDataPerID, bNumDataPerID);
	return status & this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, wTorqueLimit);
}


inline byte DynamixelQ::setWheelMode(void)
{
	return this->setWheelMode(BROADCAST_ID);
}

byte DynamixelQ::setWheelMode(const byte bID)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word  wWheelModeLimits[2] = {0, 0}, wTorqueLimit = DXL_MAX_TORQUE_LIMIT;
	
	status = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID);
	return status & this->writeWord(bID, DXL_TORQUE_LIMIT, wTorqueLimit);
}

byte DynamixelQ::setWheelMode(const byte bID[], const byte bIDLength)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wWheelModeLimits[2] = {0, 0}, wTorqueLimit = DXL_MAX_TORQUE_LIMIT;
	
	status = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID, bNumDataPerID);
	return status & this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, wTorqueLimit);
}


inline byte DynamixelQ::setMultiTurnMode(void)
{
	return this->setMultiTurnMode(BROADCAST_ID);
}

byte DynamixelQ::setMultiTurnMode(const byte bID)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wMultiTurnModeLimits[2] = {DXL_POSITION_RESOLUTION, DXL_POSITION_RESOLUTION}, wMultiTurnOffset = 0;
	
	status = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wMultiTurnModeLimits, bNumDataPerID);
	return status & this->writeWord(bID, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
}

byte DynamixelQ::setMultiTurnMode(const byte bID[], const byte bIDLength)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wMultiTurnModeLimits[2] = {DXL_POSITION_RESOLUTION, DXL_POSITION_RESOLUTION}, wMultiTurnOffset = 0;
	
	status = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wMultiTurnModeLimits, bNumDataPerID, bNumDataPerID);
	return status & this->writeWord(bID, bIDLength, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
}

inline byte DynamixelQ::zeroSpeed(void)
{
	return this->zeroSpeed(BROADCAST_ID);
}


inline byte DynamixelQ::zeroSpeed(const byte bID)
{
	const byte bNumDataPerID = 2;
	const word wSpeedTorque[2] = {0, 0};
	
	return this->syncWrite(bID, DXL_MOVING_SPEED, wSpeedTorque, bNumDataPerID);
}

inline byte DynamixelQ::zeroSpeed(const byte bID[], const byte bIDLength)
{
	const byte bNumDataPerID = 2;
	const word wSpeedTorque[2] = {0, 0};
	
	return this->syncWrite(bID, bIDLength, DXL_MOVING_SPEED, wSpeedTorque, bNumDataPerID, bNumDataPerID);
}

#endif /* DXL_UTILS_H */