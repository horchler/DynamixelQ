/*
 *	DXL_Utils.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 2-23-15, modified: 2-25-15
 */
 
#ifndef DXL_UTILS_H
#define DXL_UTILS_H

#include "DynamixelQ.h"

// DXL_RETURN_DELAY_TIME
byte DynamixelQ::setReturnDelay(const byte bReturnDelay)
{
	return this->writeByte(DXL_RETURN_DELAY_TIME, bReturnDelay & DXL_MAX_RETURN_DELAY_TIME);
}

byte DynamixelQ::setReturnDelay(const byte bID, const byte bReturnDelay)
{
	return this->writeByte(bID, DXL_RETURN_DELAY_TIME, bReturnDelay & DXL_MAX_RETURN_DELAY_TIME);
}

byte DynamixelQ::setReturnDelay(const byte bID[], const byte bIDLength, const byte bReturnDelay)
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


// DXL_GOAL_POSITION, DXL_PRESENT_POSITION
word DynamixelQ::getPosition(const byte bID)
{
	return this->readWord(bID, DXL_PRESENT_POSITION);
}

void DynamixelQ::getPosition(const byte bID[], byte bIDLength, word wPosition[])
{
	this->readWord(bID, bIDLength, DXL_PRESENT_POSITION, wPosition);
}


byte DynamixelQ::setPosition(const word wPosition)
{
	return this->writeWord(DXL_GOAL_POSITION, wPosition);
}

byte DynamixelQ::setPosition(const byte bID, const word wPosition)
{
	return this->writeWord(bID, DXL_GOAL_POSITION, wPosition);
}

byte DynamixelQ::setPosition(const byte bID[], const byte bIDLength, const word wPosition)
{
	return this->writeWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}

byte DynamixelQ::setPosition(const byte bID[], const byte bIDLength, const word wPosition[])
{
	return this->writeWord(bID, bIDLength, DXL_GOAL_POSITION, wPosition);
}


// DXL_MOVING_SPEED, DXL_PRESENT_SPEED
word DynamixelQ::getSpeed(const byte bID)
{
	return this->readWord(bID, DXL_PRESENT_SPEED);
}

void DynamixelQ::getSpeed(const byte bID[], byte bIDLength, word wSpeed[])
{
	this->readWord(bID, bIDLength, DXL_PRESENT_SPEED, wSpeed);
}


byte DynamixelQ::setSpeed(const word wSpeed)
{
	return this->writeWord(DXL_MOVING_SPEED, wSpeed);
}

byte DynamixelQ::setSpeed(const byte bID, const word wSpeed)
{
	return this->writeWord(bID, DXL_MOVING_SPEED, wSpeed);
}

byte DynamixelQ::setSpeed(const byte bID[], const byte bIDLength, const word wSpeed)
{
	return this->writeWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}

byte DynamixelQ::setSpeed(const byte bID[], const byte bIDLength, const word wSpeed[])
{
	return this->writeWord(bID, bIDLength, DXL_MOVING_SPEED, wSpeed);
}


// DXL_TORQUE_LIMIT, DXL_PRESENT_LOAD
word DynamixelQ::getLoad(const byte bID)
{
	return this->readWord(bID, DXL_PRESENT_LOAD);
}

void DynamixelQ::getLoad(const byte bID[], const byte bIDLength, word wLoad[])
{
	this->readWord(bID, bIDLength, DXL_PRESENT_LOAD, wLoad);
}


byte DynamixelQ::setLoad(const word wLoad)
{
	return this->writeWord(DXL_TORQUE_LIMIT, wLoad);
}

byte DynamixelQ::setLoad(const byte bID, const word wLoad)
{
	return this->writeWord(bID, DXL_TORQUE_LIMIT, wLoad);
}

byte DynamixelQ::setLoad(const byte bID[], const byte bIDLength, const word wLoad)
{
	return this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, wLoad);
}

byte DynamixelQ::setLoad(const byte bID[], const byte bIDLength, const word wLoad[])
{
	return this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, wLoad);
}


// DXL_ID
byte DynamixelQ::isID(const byte bID)
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


// DXL_CW_ANGLE_LIMIT, DXL_CCW_ANGLE_LIMIT
byte DynamixelQ::setJointMode(void)
{
	return this->setJointMode(BROADCAST_ID);
}

byte DynamixelQ::setJointMode(const byte bID)
{
	const byte bNumDataPerID = 2;
	const word wJointModeLimits[2] = {1, 1};
	
	return this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wJointModeLimits, bNumDataPerID);
}

byte DynamixelQ::setJointMode(const byte bID[], const byte bIDLength)
{
	const byte bNumDataPerID = 2;
	const word wJointModeLimits[2] = {1, 1};
	
	return this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wJointModeLimits, bNumDataPerID, bNumDataPerID);
}


byte DynamixelQ::setWheelMode(void)
{
	return this->setWheelMode(BROADCAST_ID);
}

byte DynamixelQ::setWheelMode(const byte bID)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wWheelModeLimits[2] = {0, 0};
	const word wTorqueLimit = 1023;
	
	status = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID);
	return status & this->writeWord(bID, DXL_TORQUE_LIMIT, wTorqueLimit);
}

byte DynamixelQ::setWheelMode(const byte bID[], const byte bIDLength)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wWheelModeLimits[2] = {0, 0};
	const word wTorqueLimit = 1023;
	
	status = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wWheelModeLimits, bNumDataPerID, bNumDataPerID);
	return status & this->writeWord(bID, bIDLength, DXL_TORQUE_LIMIT, wTorqueLimit);
}


byte DynamixelQ::setMultiTurnMode(void)
{
	return this->setMultiTurnMode(BROADCAST_ID);
}

byte DynamixelQ::setMultiTurnMode(const byte bID)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wMultiTurnModeLimits[2] = {4095, 4095};
	const word wMultiTurnOffset = 0;
	
	status = this->syncWrite(bID, DXL_CW_ANGLE_LIMIT, wMultiTurnModeLimits, bNumDataPerID);
	return status & this->writeWord(bID, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
}

byte DynamixelQ::setMultiTurnMode(const byte bID[], const byte bIDLength)
{
	byte status;
	const byte bNumDataPerID = 2;
	const word wMultiTurnModeLimits[2] = {4095, 4095};
	const word wMultiTurnOffset = 0;
	
	status = this->syncWrite(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wMultiTurnModeLimits, bNumDataPerID, bNumDataPerID);
	return status & this->writeWord(bID, bIDLength, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
}


// DXL_MOVING
byte DynamixelQ::isMoving(byte bID)
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

void DynamixelQ::isMoving(const byte bID[], const byte bIDLength, byte bBoolean[])
{
	this->readByte(bID, bIDLength, DXL_MOVING, bBoolean);
}

byte DynamixelQ::zeroSpeed(void)
{
	return this->zeroSpeed(BROADCAST_ID);
}


byte DynamixelQ::zeroSpeed(const byte bID)
{
	const byte bNumDataPerID = 2;
	const word wSpeedTorque[2] = {0, 0};
	
	return this->syncWrite(bID, DXL_MOVING_SPEED, wSpeedTorque, bNumDataPerID);
}

byte DynamixelQ::zeroSpeed(const byte bID[], const byte bIDLength)
{
	const byte bNumDataPerID = 2;
	const word wSpeedTorque[2] = {0, 0};
	
	return this->syncWrite(bID, bIDLength, DXL_MOVING_SPEED, wSpeedTorque, bNumDataPerID, bNumDataPerID);
}

#endif /* DXL_UTILS_H */