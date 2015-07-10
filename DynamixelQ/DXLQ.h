/*
 *	DXL.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-13-14, modified: 7-9-15
 *	
 *	Based on: Dynamixel.h by in2storm, 11-8-13, revised 11-12-13
 */

#ifndef DXLQ_H_
#define DXLQ_H_

#include <math.h>
#include "Timing.h"
#include "DXL_Defines.h"

class DXL
{
public:
	DXL(void);
	virtual ~DXL(void);
	
	byte begin(void);
	byte begin(byte baud);
	
	byte actuators(void);
	byte actuators(byte bID);
	byte actuators(const byte bID[], byte bIDLength);
	
	inline byte ping(byte bID);
	void ping(const byte bID[], byte bIDLength, byte bPingID[]);
	
	inline byte reset(byte bID);
	void reset(const byte bID[], byte bIDLength, byte bResetID[]);
	
	byte readByte(byte bID, byte bAddress);
	void readByte(const byte bID[], byte bIDLength, byte bAddress, byte bData[]);
	void readByte(const byte bID[], byte bIDLength, const byte bAddress[], byte bData[]);
	
	inline byte writeByte(byte bAddress, byte bData);
	byte writeByte(byte bID, byte bAddress, byte bData);
	byte writeByte(const byte bID[], byte bIDLength, byte bAddress, byte bData);
	byte writeByte(const byte bID[], byte bIDLength, byte bAddress, const byte bData[]);
	
	word readWord(byte bID, byte bAddress);
	void readWord(const byte bID[], byte bIDLength, byte bAddress, word wData[]);
	void readWord(const byte bID[], byte bIDLength, const byte bAddress[], word wData[]);
	
	inline byte writeWord(byte bAddress, word wData);
	byte writeWord(byte bID, byte bAddress, word wData);
	byte writeWord(const byte bID[], byte bIDLength, byte bAddress, word wData);
	byte writeWord(const byte bID[], byte bIDLength, byte bAddress, const word wData[]);
	
	void syncRead(const byte bID, byte bStartAddress, byte bNumAddress, word wData[]);
	void syncRead(const byte bID[], byte bIDLength, byte bStartAddress, byte bNumAddress, word wData[]);
	
	byte syncWrite(byte bStartAddress, const word wData[], byte bNumData);
	byte syncWrite(byte bID, byte bStartAddress, const word wData[], byte bNumData);
	byte syncWrite(const byte bID[], byte bIDLength, byte bStartAddress, const word wData[], byte bNumDataPerID, byte bDataLength);
	
	inline byte available(void) __attribute__((always_inline))
	{
		return this->mDxlDevice->write_pointer != this->mDxlDevice->read_pointer;
	}
	inline uint8 readRaw(void) __attribute__((always_inline))
	{
		return this->mDxlDevice->data_buffer[this->mDxlDevice->read_pointer++ & DXL_RX_BUF_SIZE];
	}
	uint8 readRaw(uint8 bData[], uint16 len);
	void writeRaw(uint8 value);
	void writeRaw(const uint8 *value, byte len);
	
	inline DXL_BOOL_TYPE isValidChecksum(const byte bData[], const byte bNumData) __attribute__((always_inline))
	{
		byte i, bChecksum = 0;
	
		for (i = 2; i < bNumData; i++) {
			bChecksum += bData[i];
		}
		return ((bChecksum & DXL_CHECKSUM_MASK) == DXL_CHECKSUM_MASK) ? DXL_TRUE : DXL_FALSE;
	}
	
	inline DXL_BAUD_RATE_VALUE getBaudRateValue(void) __attribute__((always_inline))
	{
		return this->dxl_baudRateValue;
	}
	
	inline DXL_BOOL_TYPE isBeginCalled(void) __attribute__((always_inline))
	{
		return this->dxl_beginCalled;
	}
	
	
	// DXL_Utils
	
	inline int getRetryCount(void);
	inline void setRetryCount(int retryCount);
	
	// INST_PING
	inline byte doPing(byte bID);
	void doPing(const byte bID[], byte bIDLength, byte bPingID[]);
	
	// INST_READ, INST_WRITE, INST_SYNC_WRITE
	byte getByte(byte bID, byte bAddress);
	void getByte(const byte bID[], byte bIDLength, byte bAddress, byte bData[]);
	void getByte(const byte bID[], byte bIDLength, const byte bAddress[], byte bData[]);
	
	byte setByte(byte bAddress, byte bData);
	byte setByte(byte bID, byte bAddress, byte bData);
	byte setByte(const byte bID[], byte bIDLength, byte bAddress, byte bData);
	byte setByte(const byte bID[], byte bIDLength, byte bAddress, const byte bData[]);
	
	word getWord(byte bID, const byte bAddress);
	void getWord(const byte bID[], byte bIDLength, byte bAddress, word wData[]);
	void getWord(const byte bID[], byte bIDLength, const byte bAddress[], word wData[]);
	
	byte setWord(byte bAddress, word wData);
	byte setWord(byte bID, byte bAddress, word wData);
	byte setWord(const byte bID[], byte bIDLength, byte bAddress, word wData);
	byte setWord(const byte bID[], byte bIDLength, byte bAddress, const word wData[]);
	
	// DXL_ID
	inline byte isID(byte bID);
	void isID(const byte bID[], byte bIDLength, byte bIsID[]);
	
	// DXL_BAUD_RATE
	inline word getMaxBaud(byte bID);
	void getMaxBaud(const byte bID[], byte bIDLength, byte bMaxBaud[]);
	
	// DXL_LED
	byte toggleLED(byte bLEDstate);
	void toggleLED(const byte bID[], byte bIDLength);
	
	// DXL_GOAL_POSITION, DXL_PRESENT_POSITION
	inline word getPositionResolution(byte bID);
	void getPositionResolution(const byte bID[], byte bIDLength, word wPositionResolution[]);
	
	inline word getPosition(byte bID);
	inline void getPosition(const byte bID[], byte bIDLength, word wPosition[]);
	
	inline byte setPosition(word wPosition);
	inline byte setPosition(byte bID, word wPosition);
	inline byte setPosition(const byte bID[], byte bIDLength, word wPosition);
	inline byte setPosition(const byte bID[], byte bIDLength, const word wPosition[]);
	
	// DXL_MOVING_SPEED, DXL_PRESENT_SPEED
	inline word getSpeed(byte bID);
	inline void getSpeed(const byte bID[], byte bIDLength, word wSpeed[]);
	
	inline byte setSpeed(word wSpeed);
	inline byte setSpeed(byte bID, word wSpeed);
	inline byte setSpeed(const byte bID[], byte bIDLength, word wSpeed);
	inline byte setSpeed(const byte bID[], byte bIDLength, const word wSpeed[]);
	
	// DXL_TORQUE_LIMIT, DXL_PRESENT_LOAD
	inline word getLoad(byte bID);
	inline void getLoad(const byte bID[], byte bIDLength, word wLoad[]);
	
	inline byte setLoad(word wLoad);
	inline byte setLoad(byte bID, word wLoad);
	inline byte setLoad(const byte bID[], byte bIDLength, word wLoad);
	inline byte setLoad(const byte bID[], byte bIDLength, const word wLoad[]);
	
	// DXL_REGISTERED
	inline byte isRegistered(byte bID);
	inline void isRegistered(const byte bID[], byte bIDLength, byte bRegistered[]);
	
	byte allRegistered(const byte bID[], byte bIDLength);
	byte anyRegistered(const byte bID[], byte bIDLength);
	
	// DXL_MOVING
	inline byte isMoving(byte bID);
	inline void isMoving(const byte bID[], byte bIDLength, byte bMoving[]);
	
	byte allMoving(const byte bID[], byte bIDLength);
	byte anyMoving(const byte bID[], byte bIDLength);
	
	// DXL_JOINT_MODE
	inline byte setJointMode(void);
	byte setJointMode(byte bID);
	byte setJointMode(const byte bID[], byte bIDLength);
	
	byte isJointMode(byte bID);
	void isJointMode(const byte bID[], byte bIDLength, byte bIsJointMode[]);
	
	// DXL_WHEEL_MODE
	inline byte setWheelMode(void);
	byte setWheelMode(byte bID);
	byte setWheelMode(const byte bID[], byte bIDLength);
	
	byte isWheelMode(byte bID);
	void isWheelMode(const byte bID[], byte bIDLength, byte bIsWheelMode[]);
	
	// DXL_MULTI_TURN_MODE
	inline byte setMultiTurnMode(void);
	byte setMultiTurnMode(byte bID);
	byte setMultiTurnMode(const byte bID[], byte bIDLength);
	
	byte isMultiTurnMode(byte bID);
	void isMultiTurnMode(const byte bID[], byte bIDLength, byte bIsMultiTurnMode[]);
	
	// DXL_TORQUE_CONTROL_MODE
	inline byte setTorqueControlMode(void);
	byte setTorqueControlMode(byte bID);
	byte setTorqueControlMode(const byte bID[], byte bIDLength);
	
	byte isTorqueControlMode(byte bID);
	void isTorqueControlMode(const byte bID[], byte bIDLength, byte bIsTorqueControlMode[]);
	
	// DXL_CONTROL_MODE
	inline byte getMode(byte bID);
	void getMode(const byte bID[], byte bIDLength, byte bMode[]);
	
	inline byte setMode(byte bMode);
	inline byte setMode(byte bID, byte bMode);
	void setMode(const byte bID[], byte bIDLength, const byte bMode[]);
	
	byte isMode(byte bID, byte bMode);
	void isMode(const byte bID[], byte bIDLength, const byte bMode[], byte bIsMode[]);
	
	// DXL_MOVING_SPEED, DXL_TORQUE_LIMIT
	inline byte stop(void);
	inline byte stop(byte bID);
	inline byte stop(const byte bID[], byte bIDLength);
	
	
	// DXL_GetSet
	
	// DXL_MODEL_NUMBER
	inline word getModel(byte bID);
	inline void getModel(const byte bID[], byte bIDLength, word wModelNumber[]);
	
	// DXL_VERSION_OF_FIRMWARE
	inline byte getFirmware(byte bID);
	inline void getFirmware(const byte bID[], byte bIDLength, byte bFirmwareVersion[]);
	
	// DXL_ID
	inline byte getID(byte bID);
	inline void getID(const byte bID[], byte bIDLength, byte bIDData[]);
	
	// DXL_BAUD_RATE
	inline byte getBaudRate(byte bID);
	inline void getBaudRate(const byte bID[], byte bIDLength, byte bBaudeRate[]);
	
	// DXL_RETURN_DELAY_TIME
	inline byte getReturnDelay(byte bID);
	inline void getReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay[]);
	
	inline byte setReturnDelay(byte bReturnDelay);
	inline byte setReturnDelay(byte bID, byte bReturnDelay);
	inline byte setReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay);
	byte setReturnDelay(const byte bID[], byte bIDLength, byte bReturnDelay[]);
	
	// DXL_CW_ANGLE_LIMIT
	inline word getCWAngleLimit(byte bID);
	inline void getCWAngleLimit(const byte bID[], byte bIDLength, word wCWAngleLimit[]);
	
	inline byte setCWAngleLimit(byte bID, word wCWAngleLimit);
	byte setCWAngleLimit(const byte bID[], byte bIDLength, word wCWAngleLimit);
	byte setCWAngleLimit(const byte bID[], byte bIDLength, word wCWAngleLimit[]);
	
	// DXL_CCW_ANGLE_LIMIT
	inline word getCCWAngleLimit(byte bID);
	inline void getCCWAngleLimit(const byte bID[], byte bIDLength, word wCCWAngleLimit[]);
	
	inline byte setCCWAngleLimit(byte bID, word wCCWAngleLimit);
	byte setCCWAngleLimit(const byte bID[], byte bIDLength, word wCCWAngleLimit);
	byte setCCWAngleLimit(const byte bID[], byte bIDLength, word wCCWAngleLimit[]);
	
	// DXL_THE_HIGHEST_LIMIT_TEMPERATURE
	inline byte getTemperatureLimit(byte bID);
	inline void getTemperatureLimit(const byte bID[], byte bIDLength, byte bTemperatureLimit[]);
	
	// DXL_THE_LOWEST_LIMIT_VOLTAGE
	inline byte getLowVoltageLimit(byte bID);
	inline void getLowVoltageLimit(const byte bID[], byte bIDLength, byte bLowVoltageLimit[]);
	
	inline byte setLowVoltageLimit(byte bLowVoltageLimit);
	inline byte setLowVoltageLimit(byte bID, byte bLowVoltageLimit);
	inline byte setLowVoltageLimit(const byte bID[], byte bIDLength, byte bLowVoltageLimit);
	byte setLowVoltageLimit(const byte bID[], byte bIDLength, byte bLowVoltageLimit[]);
	
	// DXL_THE_HIGHEST_LIMIT_VOLTAGE
	inline byte getHighVoltageLimit(byte bID);
	inline void getHighVoltageLimit(const byte bID[], byte bIDLength, byte bHighVoltageLimit[]);
	
	inline byte setHighVoltageLimit(byte bHighVoltageLimit);
	inline byte setHighVoltageLimit(byte bID, byte bHighVoltageLimit);
	inline byte setHighVoltageLimit(const byte bID[], byte bIDLength, byte bHighVoltageLimit);
	byte setHighVoltageLimit(const byte bID[], byte bIDLength, byte bHighVoltageLimit[]);
	
	// DXL_MAX_TORQUE
	inline word getMaxTorque(byte bID);
	inline void getMaxTorque(const byte bID[], byte bIDLength, word wMaxTorque[]);
	
	inline byte setMaxTorque(word wMaxTorque);
	inline byte setMaxTorque(byte bID, word wMaxTorque);
	byte setMaxTorque(const byte bID[], byte bIDLength, word wMaxTorque);
	byte setMaxTorque(const byte bID[], byte bIDLength, word wMaxTorque[]);
	
	// DXL_STATUS_RETURN_LEVEL
	inline byte getStatusReturnLevel(byte bID);
	inline void getStatusReturnLevel(const byte bID[], byte bIDLength, byte bStatusReturnLevel[]);
	
	inline byte setStatusReturnLevel(byte bStatusReturnLevel);
	inline byte setStatusReturnLevel(byte bID, byte bStatusReturnLevel);
	byte setStatusReturnLevel(const byte bID[], byte bIDLength, byte bStatusReturnLevel);
	byte setStatusReturnLevel(const byte bID[], byte bIDLength, const byte bStatusReturnLevel[]);
	
	// DXL_ALARM_LED
	inline byte getAlarmLED(byte bID);
	inline void getAlarmLED(const byte bID[], byte bIDLength, byte bAlarmLED[]);
	
	inline byte setAlarmLED(byte bAlarmLED);
	inline byte setAlarmLED(byte bID, byte bAlarmLED);
	byte setAlarmLED(const byte bID[], byte bIDLength, byte bAlarmLED);
	byte setAlarmLED(const byte bID[], byte bIDLength, const byte bAlarmLED[]);
	
	// DXL_ALARM_SHUTDOWN
	inline byte getAlarmShutdown(byte bID);
	inline void getAlarmShutdown(const byte bID[], byte bIDLength, byte bAlarmShutdown[]);
	
	inline byte setAlarmShutdown(byte bAlarmShutdown);
	inline byte setAlarmShutdown(byte bID, byte bAlarmShutdown);
	byte setAlarmShutdown(const byte bID[], byte bIDLength, byte bAlarmShutdown);
	byte setAlarmShutdown(const byte bID[], byte bIDLength, const byte bAlarmShutdown[]);
	
	// DXL_MULTI_TURN_OFFSET
	inline word getMultiTurnOffset(byte bID);
	inline void getMultiTurnOffset(const byte bID[], byte bIDLength, word wMultiTurnOffset[]);
	
	inline byte setMultiTurnOffset(byte bID, word wMultiTurnOffset);
	byte setMultiTurnOffset(const byte bID[], byte bIDLength, word wMultiTurnOffset);
	byte setMultiTurnOffset(const byte bID[], byte bIDLength, word wMultiTurnOffset[]);
	
	// DXL_RESOLUTION_DIVIDER
	inline byte getResolutionDivider(byte bID);
	inline void getResolutionDivider(const byte bID[], byte bIDLength, byte bResolutionDivider[]);
	
	inline byte setResolutionDivider(byte bID, byte bResolutionDivider);
	byte setResolutionDivider(const byte bID[], byte bIDLength, byte bResolutionDivider);
	byte setResolutionDivider(const byte bID[], byte bIDLength, byte bResolutionDivider[]);
	
	// DXL_TORQUE_ENABLE
	inline byte getTorqueEnable(byte bID);
	inline void getTorqueEnable(const byte bID[], byte bIDLength, byte bTorqueEnable[]);
	
	inline byte setTorqueEnable(byte bTorqueEnable);
	inline byte setTorqueEnable(byte bID, byte bTorqueEnable);
	inline byte setTorqueEnable(const byte bID[], byte bIDLength, byte bTorqueEnable);
	byte setTorqueEnable(const byte bID[], byte bIDLength, byte bTorqueEnable[]);
	
	// DXL_LED
	inline byte getLED(byte bID);
	inline void getLED(const byte bID[], byte bIDLength, byte bLEDstate[]);
	
	inline byte setLED(byte bLEDstate);
	inline byte setLED(byte bID, byte bLEDstate);
	inline byte setLED(const byte bID[], byte bIDLength, byte bLEDstate);
	byte setLED(const byte bID[], byte bIDLength, byte bLEDstate[]);
	
	// DXL_CW_COMPLIANCE_MARGIN
	inline byte getCWComplianceMargin(byte bID);
	inline void getCWComplianceMargin(const byte bID[], byte bIDLength, byte bCWComplianceMargin[]);
	
	inline byte setCWComplianceMargin(byte bID, byte bCWComplianceMargin);
	byte setCWComplianceMargin(const byte bID[], byte bIDLength, byte bCWComplianceMargin);
	byte setCWComplianceMargin(const byte bID[], byte bIDLength, const byte bCWComplianceMargin[]);
	
	// DXL_CCW_COMPLIANCE_MARGIN
	inline byte getCCWComplianceMargin(byte bID);
	inline void getCCWComplianceMargin(const byte bID[], byte bIDLength, byte bCCWComplianceMargin[]);
	
	inline byte setCCWComplianceMargin(byte bID, byte bCCWComplianceMargin);
	byte setCCWComplianceMargin(const byte bID[], byte bIDLength, byte bCCWComplianceMargin);
	byte setCCWComplianceMargin(const byte bID[], byte bIDLength, const byte bCCWComplianceMargin[]);
	
	// DXL_CW_COMPLIANCE_SLOPE
	inline byte getCWComplianceSlope(byte bID);
	inline void getCWComplianceSlope(const byte bID[], byte bIDLength, byte bCWComplianceSlope[]);
	
	inline byte setCWComplianceSlope(byte bID, byte bCWComplianceSlope);
	byte setCWComplianceSlope(const byte bID[], byte bIDLength, byte bCWComplianceSlope);
	byte setCWComplianceSlope(const byte bID[], byte bIDLength, byte bCWComplianceSlope[]);
	
	// DXL_CCW_COMPLIANCE_SLOPE
	inline byte getCCWComplianceSlope(byte bID);
	inline void getCCWComplianceSlope(const byte bID[], byte bIDLength, byte bCCWComplianceSlope[]);
	
	inline byte setCCWComplianceSlope(byte bID, byte bCCWComplianceSlope);
	byte setCCWComplianceSlope(const byte bID[], byte bIDLength, byte bCCWComplianceSlope);
	byte setCCWComplianceSlope(const byte bID[], byte bIDLength, byte bCCWComplianceSlope[]);
	
	// DXL_D_GAIN
	inline byte getDGain(byte bID);
	inline void getDGain(const byte bID[], byte bIDLength, byte bDGain[]);
	
	inline byte setDGain(byte bID, byte bDGain);
	byte setDGain(const byte bID[], byte bIDLength, byte bDGain);
	byte setDGain(const byte bID[], byte bIDLength, byte bDGain[]);
	
	// DXL_I_GAIN
	inline byte getIGain(byte bID);
	inline void getIGain(const byte bID[], byte bIDLength, byte bIGain[]);
	
	inline byte setIGain(byte bID, byte bIGain);
	byte setIGain(const byte bID[], byte bIDLength, byte bIGain);
	byte setIGain(const byte bID[], byte bIDLength, byte bIGain[]);
	
	// DXL_P_GAIN
	inline byte getPGain(byte bID);
	inline void getPGain(const byte bID[], byte bIDLength, byte bPGain[]);
	
	inline byte setPGain(byte bID, byte bPGain);
	byte setPGain(const byte bID[], byte bIDLength, byte bPGain);
	byte setPGain(const byte bID[], byte bIDLength, byte bPGain[]);
	
	// DXL_GOAL_POSITION
	inline word getGoalPosition(byte bID);
	inline void getGoalPosition(const byte bID[], byte bIDLength, word wGoalPosition[]);
	
	inline byte setGoalPosition(word wGoalPosition);
	inline byte setGoalPosition(byte bID, word wGoalPosition);
	inline byte setGoalPosition(const byte bID[], byte bIDLength, word wGoalPosition);
	inline byte setGoalPosition(const byte bID[], byte bIDLength, const word wGoalPosition[]);
	
	// DXL_MOVING_SPEED
	inline word getMovingSpeed(byte bID);
	inline void getMovingSpeed(const byte bID[], byte bIDLength, word wMovingSpeed[]);
	
	inline byte setMovingSpeed(word wMovingSpeed);
	inline byte setMovingSpeed(byte bID, word wMovingSpeed);
	inline byte setMovingSpeed(const byte bID[], byte bIDLength, word wMovingSpeed);
	inline byte setMovingSpeed(const byte bID[], byte bIDLength, const word wMovingSpeed[]);
	
	// DXL_TORQUE_LIMIT
	inline word getTorqueLimit(byte bID);
	inline void getTorqueLimit(const byte bID[], byte bIDLength, word wTorqueLimit[]);
	
	inline byte setTorqueLimit(word wTorqueLimit);
	inline byte setTorqueLimit(byte bID, word wTorqueLimit);
	inline byte setTorqueLimit(const byte bID[], byte bIDLength, word wTorqueLimit);
	inline byte setTorqueLimit(const byte bID[], byte bIDLength, const word wTorqueLimit[]);
	
	// DXL_PRESENT_POSITION
	inline word getPresentPosition(byte bID);
	inline void getPresentPosition(const byte bID[], byte bIDLength, word wPresentPosition[]);
	
	// DXL_PRESENT_SPEED
	inline word getPresentSpeed(byte bID);
	inline void getPresentSpeed(const byte bID[], byte bIDLength, word wPresentSpeed[]);
	
	// DXL_PRESENT_LOAD
	inline word getPresentLoad(byte bID);
	inline void getPresentLoad(const byte bID[], byte bIDLength, word wPresentLoad[]);
	
	// DXL_PRESENT_TEMPERATURE
	inline byte getTemperature(byte bID);
	inline void getTemperature(const byte bID[], byte bIDLength, byte bTemperature[]);
	
	// DXL_REGISTERED
	inline byte getRegistered(byte bID);
	inline void getRegistered(const byte bID[], byte bIDLength, byte bRegistered[]);
	
	// DXL_MOVING
	inline byte getMoving(byte bID);
	inline void getMoving(const byte bID[], byte bIDLength, byte bMoving[]);
	
	// DXL_LOCK
	inline byte getLock(byte bID);
	inline void getLock(const byte bID[], byte bIDLength, byte bLock[]);
	
	inline byte setLock(void);
	inline byte setLock(byte bID);
	inline byte setLock(const byte bID[], byte bIDLength);
	
	// DXL_PUNCH
	inline word getPunch(byte bID);
	inline void getPunch(const byte bID[], byte bIDLength, word wPunch[]);
	
	inline byte setPunch(word wPunch);
	inline byte setPunch(byte bID, word wPunch);
	inline byte setPunch(const byte bID[], byte bIDLength, word wPunch);
	byte setPunch(const byte bID[], byte bIDLength, word wPunch[]);
	
	// DXL_CURRENT
	inline word getCurrent(byte bID);
	inline void getCurrent(const byte bID[], byte bIDLength, word wCurrent[]);
	
	inline byte setCurrent(byte bID, word wCurrent);
	byte setCurrent(const byte bID[], byte bIDLength, word wCurrent);
	byte setCurrent(const byte bID[], byte bIDLength, word wCurrent[]);
	
	// DXL_TORQUE_CONTROL_MODE_ENABLE
	inline byte getTorqueControlEnable(byte bID);
	inline void getTorqueControlEnable(const byte bID[], byte bIDLength, byte bTorqueControlEnable[]);
	
	inline byte setTorqueControlEnable(byte bID, byte bTorqueControlEnable);
	byte setTorqueControlEnable(const byte bID[], byte bIDLength, byte bTorqueControlEnable);
	byte setTorqueControlEnable(const byte bID[], byte bIDLength, byte bTorqueControlEnable[]);
	
	// DXL_GOAL_TORQUE
	inline word getGoalTorque(byte bID);
	inline void getGoalTorque(const byte bID[], byte bIDLength, word wGoalTorque[]);
	
	inline byte setGoalTorque(byte bID, word wGoalTorque);
	byte setGoalTorque(const byte bID[], byte bIDLength, word wGoalTorque);
	byte setGoalTorque(const byte bID[], byte bIDLength, word wGoalTorque[]);
	
	// DXL_GOAL_ACCELERATION
	inline byte getGoalAcceleration(byte bID);
	inline void getGoalAcceleration(const byte bID[], byte bIDLength, byte bGoalAcceleration[]);
	
	inline byte setGoalAcceleration(byte bID, byte bGoalAcceleration);
	byte setGoalAcceleration(const byte bID[], byte bIDLength, byte bGoalAcceleration);
	byte setGoalAcceleration(const byte bID[], byte bIDLength, byte bGoalAcceleration[]);
	
	
	// DXL_Validate
	
	inline DXL_BOOL_TYPE isValidBaudRateValue(byte bBaudRateValue);
	
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
	
	void initActuatorID(byte bID);
	
	void txPacket(byte bID, DXL_INSTRUCTION bInstruction, byte bParameterLength);
	byte rxPacket(byte bID, byte bRxLength);
	byte txRxPacket(byte bID, DXL_INSTRUCTION bInst, byte bTxParaLen);
	
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
	
	DXL_BAUD_RATE_VALUE dxl_baudRateValue;
	DXL_BOOL_TYPE dxl_beginCalled;
	byte dxl_num_actuators_initialized;
	
	byte dxl_isActuatorID[DXL_MAX_ACTUATORS];
	word dxl_ModelNumber[DXL_MAX_ACTUATORS];
	
	
	// DXL_Utils
	
	inline void fillByteArray(byte bArray[], byte bArrayLength, byte bValue);
	inline void fillWordArray(word wArray[], byte bArrayLength, word wValue);
	
	byte getByteData(byte bID);
	word getWordData(byte bID);
	
	DXL_RETURN_TYPE setData(byte bID, DXL_INSTRUCTION bInstruction, byte bParamLen);
	
	
	// DXL_Validate
	
	inline DXL_BOOL_TYPE isValidActuatorID(byte bID);
	DXL_BOOL_TYPE allValidActuatorID(const byte bID[], byte bIDLength);
	
	inline DXL_BOOL_TYPE isValidID(byte bID);
	DXL_BOOL_TYPE allValidID(const byte bID[], byte bIDLength);
	
	inline DXL_BOOL_TYPE isInit(byte bID);
	void isInit(const byte bID[], byte bIDLength, byte bIsInit[]);
	
	inline DXL_BOOL_TYPE checkID(byte bID);
	
	inline DXL_SERIES getSeries(byte bID);
	void getSeries(const byte bID[], byte bIDLength, DXL_SERIES bSeries[]);
	
	inline DXL_SERIES_TYPE getSeriesType(byte bID);
	void getSeriesType(const byte bID[], byte bIDLength, DXL_SERIES_TYPE bSeries[]);
	
	inline DXL_BOOL_TYPE isByteAddressValid(byte bID, byte bAddress);
	
	inline DXL_BOOL_TYPE isByteAddress(byte bID, byte bAddress);
	inline DXL_BOOL_TYPE isWordAddress(byte bID, byte bAddress);
	
	inline DXL_BOOL_TYPE isValidByte(byte bData);
	inline void isValidByte(const byte bData[], byte bDataLength, byte bValidByte[]);
	inline DXL_BOOL_TYPE allValidByte(const byte bData[], byte bDataLength);
	
	inline DXL_BOOL_TYPE isValidWord(word wData);
	inline void isValidWord(const word wData[], byte bDataLength, byte bValidWord[]);
	inline DXL_BOOL_TYPE allValidWord(const word wData[], byte bDataLength);
	
	inline DXL_BOOL_TYPE isAddressWritable(byte bID, byte bAddress);
	inline void isAddressWritable(byte bID, const byte bAddress[], byte bNumAddress, byte bWritable[]);
};

#endif /* DXLQ_H_ */