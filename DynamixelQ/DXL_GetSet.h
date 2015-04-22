/*
 *	DXL_GetSet.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 2-23-15, modified: 4-12-15
 */
 
#ifndef DXL_GETSET_H_
#define DXL_GETSET_H_

// DXL_MODEL_NUMBER
inline word DXLQ::getModel(const byte bID)
{
	return this->getWord(bID, DXL_MODEL_NUMBER);
}

inline void DXLQ::getModel(const byte bID[], const byte bIDLength, word wModelNumber[])
{
	this->getWord(bID, bIDLength, DXL_MODEL_NUMBER, wModelNumber);
}


// DXL_VERSION_OF_FIRMWARE
inline byte DXLQ::getFirmware(const byte bID)
{
	return this->getByte(bID, DXL_VERSION_OF_FIRMWARE);
}

inline void DXLQ::getFirmware(const byte bID[], const byte bIDLength, byte bFirmwareVersion[])
{
	this->getByte(bID, bIDLength, DXL_VERSION_OF_FIRMWARE, bFirmwareVersion);
}


// DXL_ID
inline byte DXLQ::getID(const byte bID)
{
	return this->getByte(bID, DXL_ID);
}

inline void DXLQ::getID(const byte bID[], const byte bIDLength, byte bIDData[])
{
	this->getByte(bID, bIDLength, DXL_ID, bIDData);
}


// DXL_BAUD_RATE
inline byte DXLQ::getBaudRate(const byte bID)
{
	return this->getByte(bID, DXL_BAUD_RATE);
}

inline void DXLQ::getBaudRate(const byte bID[], const byte bIDLength, byte bBaudRate[])
{
	this->getByte(bID, bIDLength, DXL_BAUD_RATE, bBaudRate);
}


// DXL_RETURN_DELAY_TIME
inline byte DXLQ::getReturnDelay(const byte bID)
{
	return this->getByte(bID, DXL_RETURN_DELAY_TIME);
}

inline void DXLQ::getReturnDelay(const byte bID[], const byte bIDLength, byte bReturnDelay[])
{
	this->getByte(bID, bIDLength, DXL_RETURN_DELAY_TIME, bReturnDelay);
}


inline byte DXLQ::setReturnDelay(const byte bReturnDelay)
{
	return this->setByte(DXL_RETURN_DELAY_TIME, DXL_MIN(bReturnDelay, DXL_MAX_RETURN_DELAY_TIME));
}

inline byte DXLQ::setReturnDelay(const byte bID, const byte bReturnDelay)
{
	return this->setByte(bID, DXL_RETURN_DELAY_TIME, DXL_MIN(bReturnDelay, DXL_MAX_RETURN_DELAY_TIME));
}

inline byte DXLQ::setReturnDelay(const byte bID[], const byte bIDLength, const byte bReturnDelay)
{
	return this->setByte(bID, bIDLength, DXL_RETURN_DELAY_TIME, DXL_MIN(bReturnDelay, DXL_MAX_RETURN_DELAY_TIME));
}

byte DXLQ::setReturnDelay(const byte bID[], const byte bIDLength, byte bReturnDelay[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bReturnDelay[i] = DXL_MIN(bReturnDelay[i], DXL_MAX_RETURN_DELAY_TIME);
	}
	return this->setByte(bID, bIDLength, DXL_RETURN_DELAY_TIME, bReturnDelay);
}


// DXL_CW_ANGLE_LIMIT
inline word DXLQ::getCWAngleLimit(const byte bID)
{
	return this->getWord(bID, DXL_CW_ANGLE_LIMIT);
}

inline void DXLQ::getCWAngleLimit(const byte bID[], const byte bIDLength, word wCWAngleLimit[])
{
	this->getWord(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wCWAngleLimit);
}


inline byte DXLQ::setCWAngleLimit(const byte bID, const word wCWAngleLimit)
{
	return this->setWord(bID, DXL_CW_ANGLE_LIMIT, DXL_MIN(wCWAngleLimit, this->getPositionResolution(bID)));
}

byte DXLQ::setCWAngleLimit(const byte bID[], const byte bIDLength, const word wCWAngleLimit)
{
	byte i, bSameType = DXL_TRUE;
	word wData[bIDLength];
	
	wData[0] = DXL_MIN(wCWAngleLimit, this->getPositionResolution(bID[0]));
	for (i = 1; i < bIDLength; i++) {
		wData[i] = DXL_MIN(wCWAngleLimit, this->getPositionResolution(bID[i]));
		if (wData[i] != wData[0]) {
			bSameType = DXL_FALSE;
		}
	}
	return bSameType ? this->setWord(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wData[0]) : this->setWord(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wData);
}

byte DXLQ::setCWAngleLimit(const byte bID[], const byte bIDLength, word wCWAngleLimit[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		wCWAngleLimit[i] = DXL_MIN(wCWAngleLimit[i], this->getPositionResolution(bID[i]));
	}
	return this->setWord(bID, bIDLength, DXL_CW_ANGLE_LIMIT, wCWAngleLimit);
}


// DXL_CCW_ANGLE_LIMIT
inline word DXLQ::getCCWAngleLimit(const byte bID)
{
	return this->getWord(bID, DXL_CCW_ANGLE_LIMIT);
}

inline void DXLQ::getCCWAngleLimit(const byte bID[], const byte bIDLength, word wCCWAngleLimit[])
{
	this->getWord(bID, bIDLength, DXL_CCW_ANGLE_LIMIT, wCCWAngleLimit);
}


inline byte DXLQ::setCCWAngleLimit(const byte bID, const word wCCWAngleLimit)
{
	return this->setWord(bID, DXL_CCW_ANGLE_LIMIT, DXL_MIN(wCCWAngleLimit, this->getPositionResolution(bID)));
}

byte DXLQ::setCCWAngleLimit(const byte bID[], const byte bIDLength, const word wCCWAngleLimit)
{
	byte i, bSameType = DXL_TRUE;
	word wData[bIDLength];
	
	wData[0] = DXL_MIN(wCCWAngleLimit, this->getPositionResolution(bID[0]));
	for (i = 1; i < bIDLength; i++) {
		wData[i] = DXL_MIN(wCCWAngleLimit, this->getPositionResolution(bID[i]));
		if (wData[i] != wData[0]) {
			bSameType = DXL_FALSE;
		}
	}
	return bSameType ? this->setWord(bID, bIDLength, DXL_CCW_ANGLE_LIMIT, wData[0]) : this->setWord(bID, bIDLength, DXL_CCW_ANGLE_LIMIT, wData);
}

byte DXLQ::setCCWAngleLimit(const byte bID[], const byte bIDLength, word wCCWAngleLimit[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		wCCWAngleLimit[i] = DXL_MIN(wCCWAngleLimit[i], this->getPositionResolution(bID[i]));
	}
	return this->setWord(bID, bIDLength, DXL_CCW_ANGLE_LIMIT, wCCWAngleLimit);
}

	
// DXL_THE_HIGHEST_LIMIT_TEMPERATURE
inline byte DXLQ::getTemperatureLimit(const byte bID)
{
	return this->getByte(bID, DXL_THE_HIGHEST_LIMIT_TEMPERATURE);
}

inline void DXLQ::getTemperatureLimit(const byte bID[], const byte bIDLength, byte bTemperatureLimit[])
{
	this->getByte(bID, bIDLength, DXL_THE_HIGHEST_LIMIT_TEMPERATURE, bTemperatureLimit);
}


// DXL_THE_LOWEST_LIMIT_VOLTAGE
inline byte DXLQ::getLowVoltageLimit(const byte bID)
{
	return this->getByte(bID, DXL_THE_LOWEST_LIMIT_VOLTAGE);
}

inline void DXLQ::getLowVoltageLimit(const byte bID[], const byte bIDLength, byte bLowVoltageLimit[])
{
	this->getByte(bID, bIDLength, DXL_THE_LOWEST_LIMIT_VOLTAGE, bLowVoltageLimit);
}


inline byte DXLQ::setLowVoltageLimit(const byte bLowVoltageLimit)
{
	return this->setByte(DXL_THE_LOWEST_LIMIT_VOLTAGE, DXL_MIN(DXL_MAX(bLowVoltageLimit, DXL_MIN_LIMIT_VOLTAGE), DXL_MAX_LIMIT_VOLTAGE));
}

inline byte DXLQ::setLowVoltageLimit(const byte bID, const byte bLowVoltageLimit)
{
	return this->setByte(bID, DXL_THE_LOWEST_LIMIT_VOLTAGE, DXL_MIN(DXL_MAX(bLowVoltageLimit, DXL_MIN_LIMIT_VOLTAGE), DXL_MAX_LIMIT_VOLTAGE));
}

inline byte DXLQ::setLowVoltageLimit(const byte bID[], const byte bIDLength, const byte bLowVoltageLimit)
{
	return this->setByte(bID, bIDLength, DXL_THE_LOWEST_LIMIT_VOLTAGE, DXL_MIN(DXL_MAX(bLowVoltageLimit, DXL_MIN_LIMIT_VOLTAGE), DXL_MAX_LIMIT_VOLTAGE));
}

byte DXLQ::setLowVoltageLimit(const byte bID[], const byte bIDLength, byte bLowVoltageLimit[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bLowVoltageLimit[i] = DXL_MIN(DXL_MAX(bLowVoltageLimit[i], DXL_MIN_LIMIT_VOLTAGE), DXL_MAX_LIMIT_VOLTAGE);
	}
	return this->setByte(bID, bIDLength, DXL_THE_LOWEST_LIMIT_VOLTAGE, bLowVoltageLimit);
}


// DXL_THE_HIGHEST_LIMIT_VOLTAGE
inline byte DXLQ::getHighVoltageLimit(const byte bID)
{
	return this->getByte(bID, DXL_THE_HIGHEST_LIMIT_VOLTAGE);
}

inline void DXLQ::getHighVoltageLimit(const byte bID[], const byte bIDLength, byte bHighVoltageLimit[])
{
	this->getByte(bID, bIDLength, DXL_THE_HIGHEST_LIMIT_VOLTAGE, bHighVoltageLimit);
}


inline byte DXLQ::setHighVoltageLimit(const byte bHighVoltageLimit)
{
	return this->setByte(DXL_THE_HIGHEST_LIMIT_VOLTAGE, DXL_MIN(DXL_MAX(bHighVoltageLimit, DXL_MIN_LIMIT_VOLTAGE), DXL_MAX_LIMIT_VOLTAGE));
}

inline byte DXLQ::setHighVoltageLimit(const byte bID, const byte bHighVoltageLimit)
{
	return this->setByte(bID, DXL_THE_HIGHEST_LIMIT_VOLTAGE, DXL_MIN(DXL_MAX(bHighVoltageLimit, DXL_MIN_LIMIT_VOLTAGE), DXL_MAX_LIMIT_VOLTAGE));
}

inline byte DXLQ::setHighVoltageLimit(const byte bID[], const byte bIDLength, const byte bHighVoltageLimit)
{
	return this->setByte(bID, bIDLength, DXL_THE_HIGHEST_LIMIT_VOLTAGE, DXL_MIN(DXL_MAX(bHighVoltageLimit, DXL_MIN_LIMIT_VOLTAGE), DXL_MAX_LIMIT_VOLTAGE));
}

byte DXLQ::setHighVoltageLimit(const byte bID[], const byte bIDLength, byte bHighVoltageLimit[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bHighVoltageLimit[i] = DXL_MIN(DXL_MAX(bHighVoltageLimit[i], DXL_MIN_LIMIT_VOLTAGE), DXL_MAX_LIMIT_VOLTAGE);
	}
	return this->setByte(bID, bIDLength, DXL_THE_HIGHEST_LIMIT_VOLTAGE, bHighVoltageLimit);
}


// DXL_MAX_TORQUE
inline word DXLQ::getMaxTorque(const byte bID)
{
	return this->getWord(bID, DXL_MAX_TORQUE);
}

inline void DXLQ::getMaxTorque(const byte bID[], const byte bIDLength, word wMaxTorque[])
{
	this->getWord(bID, bIDLength, DXL_MAX_TORQUE, wMaxTorque);
}


inline byte DXLQ::setMaxTorque(const word wMaxTorque)
{
	return this->setWord(DXL_MAX_TORQUE, DXL_MIN(wMaxTorque, DXL_MAX_TORQUE_LIMIT));
}

inline byte DXLQ::setMaxTorque(const byte bID, const word wMaxTorque)
{
	return this->setWord(bID, DXL_MAX_TORQUE, DXL_MIN(wMaxTorque, DXL_MAX_TORQUE_LIMIT));
}

inline byte DXLQ::setMaxTorque(const byte bID[], const byte bIDLength, const word wMaxTorque)
{
	return this->setWord(bID, bIDLength, DXL_MAX_TORQUE, DXL_MIN(wMaxTorque, DXL_MAX_TORQUE_LIMIT));
}

byte DXLQ::setMaxTorque(const byte bID[], const byte bIDLength, word wMaxTorque[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		wMaxTorque[i] = DXL_MIN(wMaxTorque[i], DXL_MAX_TORQUE_LIMIT);
	}
	return this->setWord(bID, bIDLength, DXL_MAX_TORQUE, wMaxTorque);
}


// DXL_STATUS_RETURN_LEVEL
inline byte DXLQ::getStatusReturnLevel(const byte bID)
{
	return this->getByte(bID, DXL_STATUS_RETURN_LEVEL);
}

inline void DXLQ::getStatusReturnLevel(const byte bID[], const byte bIDLength, byte bStatusReturnLevel[])
{
	this->getByte(bID, bIDLength, DXL_STATUS_RETURN_LEVEL, bStatusReturnLevel);
}


inline byte DXLQ::setStatusReturnLevel(const byte bStatusReturnLevel)
{
	if (bStatusReturnLevel <= DXL_STATUS_RETURN_ALL) {
		return this->setByte(DXL_STATUS_RETURN_LEVEL, bStatusReturnLevel);
	}
	return DXL_FAILURE;
}

inline byte DXLQ::setStatusReturnLevel(const byte bID, const byte bStatusReturnLevel)
{
	if (bStatusReturnLevel <= DXL_STATUS_RETURN_ALL) {
		return this->setByte(bID, DXL_STATUS_RETURN_LEVEL, bStatusReturnLevel);
	}
	return DXL_FAILURE;
}

byte DXLQ::setStatusReturnLevel(const byte bID[], const byte bIDLength, const byte bStatusReturnLevel)
{
	if (bStatusReturnLevel <= DXL_STATUS_RETURN_ALL) {
		return this->setByte(bID, bIDLength, DXL_STATUS_RETURN_LEVEL, bStatusReturnLevel);
	}
	return DXL_FAILURE;
}

byte DXLQ::setStatusReturnLevel(const byte bID[], const byte bIDLength, const byte bStatusReturnLevel[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bStatusReturnLevel[i] > DXL_STATUS_RETURN_ALL) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_STATUS_RETURN_LEVEL, bStatusReturnLevel);
}


// DXL_ALARM_LED
inline byte DXLQ::getAlarmLED(const byte bID)
{
	return this->getByte(bID, DXL_ALARM_LED);
}

inline void DXLQ::getAlarmLED(const byte bID[], const byte bIDLength, byte bAlarmLED[])
{
	this->getByte(bID, bIDLength, DXL_ALARM_LED, bAlarmLED);
}


inline byte DXLQ::setAlarmLED(const byte bAlarmLED)
{
	if (bAlarmLED <= DXL_MAX_ALARM_ERROR) {
		return this->setByte(DXL_ALARM_LED, bAlarmLED);
	}
	return DXL_FAILURE;
}

inline byte DXLQ::setAlarmLED(const byte bID, const byte bAlarmLED)
{
	if (bAlarmLED <= DXL_MAX_ALARM_ERROR) {
		return this->setByte(bID, DXL_ALARM_LED, bAlarmLED);
	}
	return DXL_FAILURE;
}

byte DXLQ::setAlarmLED(const byte bID[], const byte bIDLength, const byte bAlarmLED)
{
	if (bAlarmLED <= DXL_MAX_ALARM_ERROR) {
		return this->setByte(bID, bIDLength, DXL_ALARM_LED, bAlarmLED);
	}
	return DXL_FAILURE;
}

byte DXLQ::setAlarmLED(const byte bID[], const byte bIDLength, const byte bAlarmLED[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bAlarmLED[i] > DXL_MAX_ALARM_ERROR) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_ALARM_LED, bAlarmLED);
}


// DXL_ALARM_SHUTDOWN
inline byte DXLQ::getAlarmShutdown(const byte bID)
{
	return this->getByte(bID, DXL_ALARM_SHUTDOWN);
}

inline void DXLQ::getAlarmShutdown(const byte bID[], const byte bIDLength, byte bAlarmShutdown[])
{
	this->getByte(bID, bIDLength, DXL_ALARM_SHUTDOWN, bAlarmShutdown);
}


inline byte DXLQ::setAlarmShutdown(const byte bAlarmShutdown)
{
	if (bAlarmShutdown <= DXL_MAX_ALARM_ERROR) {
		return this->setByte(DXL_ALARM_SHUTDOWN, bAlarmShutdown);
	}
	return DXL_FAILURE;
}

inline byte DXLQ::setAlarmShutdown(const byte bID, const byte bAlarmShutdown)
{
	if (bAlarmShutdown <= DXL_MAX_ALARM_ERROR) {
		return this->setByte(bID, DXL_ALARM_SHUTDOWN, bAlarmShutdown);
	}
	return DXL_FAILURE;
}

byte DXLQ::setAlarmShutdown(const byte bID[], const byte bIDLength, const byte bAlarmShutdown)
{
	if (bAlarmShutdown <= DXL_MAX_ALARM_ERROR) {
		return this->setByte(bID, bIDLength, DXL_ALARM_SHUTDOWN, bAlarmShutdown);
	}
	return DXL_FAILURE;
}

byte DXLQ::setAlarmShutdown(const byte bID[], const byte bIDLength, const byte bAlarmShutdown[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bAlarmShutdown[i] > DXL_MAX_ALARM_ERROR) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_ALARM_SHUTDOWN, bAlarmShutdown);
}


// DXL_MULTI_TURN_OFFSET
inline word DXLQ::getMultiTurnOffset(const byte bID)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->getWord(bID, DXL_MULTI_TURN_OFFSET);
	}
	return DXL_INVALID_WORD;
}

inline void DXLQ::getMultiTurnOffset(const byte bID[], const byte bIDLength, word wMultiTurnOffset[])
{
	this->getWord(bID, bIDLength, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
}


inline byte DXLQ::setMultiTurnOffset(const byte bID, const word wMultiTurnOffset)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->setWord(bID, DXL_MULTI_TURN_OFFSET, DXL_MIN(wMultiTurnOffset, DXL_MX_MAX_MULTI_TURN_OFFSET_MAGNITUDE));
	}
	return DXL_FAILURE;
}

byte DXLQ::setMultiTurnOffset(const byte bID[], const byte bIDLength, const word wMultiTurnOffset)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setWord(bID, bIDLength, DXL_MULTI_TURN_OFFSET, DXL_MIN(wMultiTurnOffset, DXL_MX_MAX_MULTI_TURN_OFFSET_MAGNITUDE));
}

byte DXLQ::setMultiTurnOffset(const byte bID[], const byte bIDLength, word wMultiTurnOffset[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
		wMultiTurnOffset[i] = DXL_MIN(wMultiTurnOffset[i], DXL_MX_MAX_MULTI_TURN_OFFSET_MAGNITUDE);
	}
	return this->setWord(bID, bIDLength, DXL_MULTI_TURN_OFFSET, wMultiTurnOffset);
}


// DXL_RESOLUTION_DIVIDER
inline byte DXLQ::getResolutionDivider(const byte bID)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->getByte(bID, DXL_RESOLUTION_DIVIDER);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getResolutionDivider(const byte bID[], const byte bIDLength, byte bResolutionDivider[])
{
	this->getByte(bID, bIDLength, DXL_RESOLUTION_DIVIDER, bResolutionDivider);
}


inline byte DXLQ::setResolutionDivider(const byte bID, const byte bResolutionDivider)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->setByte(bID, DXL_RESOLUTION_DIVIDER, DXL_MIN(DXL_MAX(bResolutionDivider, DXL_MX_MIN_RESOLUTION_DIVIDER), DXL_MX_MAX_RESOLUTION_DIVIDER));
	}
	return DXL_FAILURE;
}

byte DXLQ::setResolutionDivider(const byte bID[], const byte bIDLength, const byte bResolutionDivider)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_RESOLUTION_DIVIDER, DXL_MIN(DXL_MAX(bResolutionDivider, DXL_MX_MIN_RESOLUTION_DIVIDER), DXL_MX_MAX_RESOLUTION_DIVIDER));
}

byte DXLQ::setResolutionDivider(const byte bID[], const byte bIDLength, byte bResolutionDivider[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
		bResolutionDivider[i] = DXL_MIN(DXL_MAX(bResolutionDivider[i], DXL_MX_MIN_RESOLUTION_DIVIDER), DXL_MX_MAX_RESOLUTION_DIVIDER);
	}
	return this->setByte(bID, bIDLength, DXL_RESOLUTION_DIVIDER, bResolutionDivider);
}

	
// DXL_TORQUE_ENABLE
inline byte DXLQ::getTorqueEnable(const byte bID)
{
	return this->getByte(bID, DXL_TORQUE_ENABLE);
}
	
inline void DXLQ::getTorqueEnable(const byte bID[], const byte bIDLength, byte bTorqueEnable[])
{
	this->getByte(bID, bIDLength, DXL_TORQUE_ENABLE, bTorqueEnable);
}


inline byte DXLQ::setTorqueEnable(const byte bTorqueEnable)
{
	return this->setByte(DXL_TORQUE_ENABLE, !!bTorqueEnable);
}

inline byte DXLQ::setTorqueEnable(const byte bID, const byte bTorqueEnable)
{
	return this->setByte(bID, DXL_TORQUE_ENABLE, !!bTorqueEnable);
}

inline byte DXLQ::setTorqueEnable(const byte bID[], const byte bIDLength, const byte bTorqueEnable)
{
	return this->setByte(bID, bIDLength, DXL_TORQUE_ENABLE, !!bTorqueEnable);
}

byte DXLQ::setTorqueEnable(const byte bID[], const byte bIDLength, byte bTorqueEnable[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bTorqueEnable[i] = !!bTorqueEnable[i];
	}
	return this->setByte(bID, bIDLength, DXL_TORQUE_ENABLE, bTorqueEnable);
}


// DXL_LED
inline byte DXLQ::getLED(const byte bID)
{
	return this->getByte(bID, DXL_LED);
}
	
inline void DXLQ::getLED(const byte bID[], const byte bIDLength, byte bLEDstate[])
{
	this->getByte(bID, bIDLength, DXL_LED, bLEDstate);
}


inline byte DXLQ::setLED(const byte bLEDstate)
{
	return this->setByte(DXL_LED, !!bLEDstate);
}

inline byte DXLQ::setLED(const byte bID, const byte bLEDstate)
{
	return this->setByte(bID, DXL_LED, !!bLEDstate);
}

inline byte DXLQ::setLED(const byte bID[], const byte bIDLength, const byte bLEDstate)
{
	return this->setByte(bID, bIDLength, DXL_LED, !!bLEDstate);
}

byte DXLQ::setLED(const byte bID[], const byte bIDLength, byte bLEDstate[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bLEDstate[i] = !!bLEDstate[i];
	}
	return this->setByte(bID, bIDLength, DXL_LED, bLEDstate);
}


// DXL_CW_COMPLIANCE_MARGIN
inline byte DXLQ::getCWComplianceMargin(const byte bID)
{
	if (this->getSeries(bID) == DXL_AX_SERIES) {
		return this->getByte(bID, DXL_CW_COMPLIANCE_MARGIN);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getCWComplianceMargin(const byte bID[], const byte bIDLength, byte bCWComplianceMargin[])
{
	this->getByte(bID, bIDLength, DXL_CW_COMPLIANCE_MARGIN, bCWComplianceMargin);
}


inline byte DXLQ::setCWComplianceMargin(const byte bID, const byte bCWComplianceMargin)
{
	if (this->getSeries(bID) == DXL_AX_SERIES) {
		return this->setByte(bID, DXL_CW_COMPLIANCE_MARGIN, bCWComplianceMargin);
	}
	return DXL_FAILURE;
}

byte DXLQ::setCWComplianceMargin(const byte bID[], const byte bIDLength, const byte bCWComplianceMargin)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_AX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_CW_COMPLIANCE_MARGIN, bCWComplianceMargin);
}

byte DXLQ::setCWComplianceMargin(const byte bID[], const byte bIDLength, const byte bCWComplianceMargin[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_AX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_CW_COMPLIANCE_MARGIN, bCWComplianceMargin);
}


// DXL_CCW_COMPLIANCE_MARGIN
inline byte DXLQ::getCCWComplianceMargin(const byte bID)
{
	if (this->getSeries(bID) == DXL_AX_SERIES) {
		return this->getByte(bID, DXL_CCW_COMPLIANCE_MARGIN);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getCCWComplianceMargin(const byte bID[], const byte bIDLength, byte bCCWComplianceMargin[])
{
	this->getByte(bID, bIDLength, DXL_CCW_COMPLIANCE_MARGIN, bCCWComplianceMargin);
}


inline byte DXLQ::setCCWComplianceMargin(const byte bID, const byte bCCWComplianceMargin)
{
	if (this->getSeries(bID) == DXL_AX_SERIES) {
		return this->setByte(bID, DXL_CCW_COMPLIANCE_MARGIN, bCCWComplianceMargin);
	}
	return DXL_FAILURE;
}

byte DXLQ::setCCWComplianceMargin(const byte bID[], const byte bIDLength, const byte bCCWComplianceMargin)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_AX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_CCW_COMPLIANCE_MARGIN, bCCWComplianceMargin);
}

byte DXLQ::setCCWComplianceMargin(const byte bID[], const byte bIDLength, const byte bCCWComplianceMargin[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_AX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_CCW_COMPLIANCE_MARGIN, bCCWComplianceMargin);
}


// DXL_CW_COMPLIANCE_SLOPE
inline byte DXLQ::getCWComplianceSlope(const byte bID)
{
	if (this->getSeries(bID) == DXL_AX_SERIES) {
		return this->getByte(bID, DXL_CW_COMPLIANCE_SLOPE);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getCWComplianceSlope(const byte bID[], const byte bIDLength, byte bCWComplianceSlope[])
{
	this->getByte(bID, bIDLength, DXL_CW_COMPLIANCE_SLOPE, bCWComplianceSlope);
}


inline byte DXLQ::setCWComplianceSlope(const byte bID, const byte bCWComplianceSlope)
{
	if (this->getSeries(bID) == DXL_AX_SERIES) {
		return this->setByte(bID, DXL_CW_COMPLIANCE_SLOPE, DXL_AX_COMPLIANCE_SLOPE(bCWComplianceSlope));
	}
	return DXL_FAILURE;
}

byte DXLQ::setCWComplianceSlope(const byte bID[], const byte bIDLength, const byte bCWComplianceSlope)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_AX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_CW_COMPLIANCE_SLOPE, DXL_AX_COMPLIANCE_SLOPE(bCWComplianceSlope));
}

byte DXLQ::setCWComplianceSlope(const byte bID[], const byte bIDLength, byte bCWComplianceSlope[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_AX_SERIES) {
			return DXL_FAILURE;
		}
		bCWComplianceSlope[i] = DXL_AX_COMPLIANCE_SLOPE(bCWComplianceSlope[i]);
	}
	return this->setByte(bID, bIDLength, DXL_CW_COMPLIANCE_SLOPE, bCWComplianceSlope);
}


// DXL_CCW_COMPLIANCE_SLOPE
inline byte DXLQ::getCCWComplianceSlope(const byte bID)
{
	if (this->getSeries(bID) == DXL_AX_SERIES) {
		return this->getByte(bID, DXL_CCW_COMPLIANCE_SLOPE);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getCCWComplianceSlope(const byte bID[], const byte bIDLength, byte bCCWComplianceSlope[])
{
	this->getByte(bID, bIDLength, DXL_CCW_COMPLIANCE_SLOPE, bCCWComplianceSlope);
}


inline byte DXLQ::setCCWComplianceSlope(const byte bID, const byte bCCWComplianceSlope)
{
	if (this->getSeries(bID) == DXL_AX_SERIES) {
		return this->setByte(bID, DXL_CCW_COMPLIANCE_SLOPE, DXL_AX_COMPLIANCE_SLOPE(bCCWComplianceSlope));
	}
	return DXL_FAILURE;
}

byte DXLQ::setCCWComplianceSlope(const byte bID[], const byte bIDLength, const byte bCCWComplianceSlope)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_AX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_CCW_COMPLIANCE_SLOPE, DXL_AX_COMPLIANCE_SLOPE(bCCWComplianceSlope));
}

byte DXLQ::setCCWComplianceSlope(const byte bID[], const byte bIDLength, byte bCCWComplianceSlope[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_AX_SERIES) {
			return DXL_FAILURE;
		}
		bCCWComplianceSlope[i] = DXL_AX_COMPLIANCE_SLOPE(bCCWComplianceSlope[i]);
	}
	return this->setByte(bID, bIDLength, DXL_CCW_COMPLIANCE_SLOPE, bCCWComplianceSlope);
}


// DXL_D_GAIN
inline byte DXLQ::getDGain(const byte bID)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->getByte(bID, DXL_D_GAIN);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getDGain(const byte bID[], const byte bIDLength, byte bDGain[])
{
	this->getByte(bID, bIDLength, DXL_D_GAIN, bDGain);
}


inline byte DXLQ::setDGain(const byte bID, const byte bDGain)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->setByte(bID, DXL_D_GAIN, DXL_MIN(bDGain, DXL_MX_MAX_GAIN));
	}
	return DXL_FAILURE;
}

byte DXLQ::setDGain(const byte bID[], const byte bIDLength, const byte bDGain)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_D_GAIN, DXL_MIN(bDGain, DXL_MX_MAX_GAIN));
}

byte DXLQ::setDGain(const byte bID[], const byte bIDLength, byte bDGain[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
		bDGain[i] = DXL_MIN(bDGain[i], DXL_MX_MAX_GAIN);
	}
	return this->setByte(bID, bIDLength, DXL_D_GAIN, bDGain);
}


// DXL_I_GAIN
inline byte DXLQ::getIGain(const byte bID)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->getByte(bID, DXL_I_GAIN);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getIGain(const byte bID[], const byte bIDLength, byte bIGain[])
{
	this->getByte(bID, bIDLength, DXL_I_GAIN, bIGain);
}


inline byte DXLQ::setIGain(const byte bID, const byte bIGain)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->setByte(bID, DXL_I_GAIN, DXL_MIN(bIGain, DXL_MX_MAX_GAIN));
	}
	return DXL_FAILURE;
}

byte DXLQ::setIGain(const byte bID[], const byte bIDLength, const byte bIGain)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_I_GAIN, DXL_MIN(bIGain, DXL_MX_MAX_GAIN));
}

byte DXLQ::setIGain(const byte bID[], const byte bIDLength, byte bIGain[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
		bIGain[i] = DXL_MIN(bIGain[i], DXL_MX_MAX_GAIN);
	}
	return this->setByte(bID, bIDLength, DXL_I_GAIN, bIGain);
}


// DXL_P_GAIN
inline byte DXLQ::getPGain(const byte bID)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->getByte(bID, DXL_P_GAIN);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getPGain(const byte bID[], const byte bIDLength, byte bPGain[])
{
	this->getByte(bID, bIDLength, DXL_P_GAIN, bPGain);
}


inline byte DXLQ::setPGain(const byte bID, const byte bPGain)
{
	if (this->getSeries(bID) == DXL_MX_SERIES) {
		return this->setByte(bID, DXL_P_GAIN, DXL_MIN(bPGain, DXL_MX_MAX_GAIN));
	}
	return DXL_FAILURE;
}

byte DXLQ::setPGain(const byte bID[], const byte bIDLength, const byte bPGain)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_P_GAIN, DXL_MIN(bPGain, DXL_MX_MAX_GAIN));
}

byte DXLQ::setPGain(const byte bID[], const byte bIDLength, byte bPGain[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeries(bID[i]) != DXL_MX_SERIES) {
			return DXL_FAILURE;
		}
		bPGain[i] = DXL_MIN(bPGain[i], DXL_MX_MAX_GAIN);
	}
	return this->setByte(bID, bIDLength, DXL_P_GAIN, bPGain);
}


// DXL_GOAL_POSITION
inline word DXLQ::getGoalPosition(const byte bID)
{
	return this->getWord(bID, DXL_GOAL_POSITION);
}

inline void DXLQ::getGoalPosition(const byte bID[], const byte bIDLength, word wGoalPosition[])
{
	this->getWord(bID, bIDLength, DXL_GOAL_POSITION, wGoalPosition);
}


// TODO: Handle BROADCAST_ID case for mixed actuator types
inline byte DXLQ::setGoalPosition(const word wGoalPosition)
{
	return this->setWord(DXL_GOAL_POSITION, wGoalPosition);
}
// TODO: Handle BROADCAST_ID case for mixed actuator types
inline byte DXLQ::setGoalPosition(const byte bID, const word wGoalPosition)
{
	return this->setWord(bID, DXL_GOAL_POSITION, wGoalPosition);
}

inline byte DXLQ::setGoalPosition(const byte bID[], const byte bIDLength, const word wGoalPosition)
{
	//byte i;
	//word wData[bIDLength];
	
	//this->getPositionResolution(bID[i]);
	return this->setWord(bID, bIDLength, DXL_GOAL_POSITION, wGoalPosition);
}

inline byte DXLQ::setGoalPosition(const byte bID[], const byte bIDLength, const word wGoalPosition[])
{
	return this->setWord(bID, bIDLength, DXL_GOAL_POSITION, wGoalPosition);
}


// DXL_MOVING_SPEED
inline word DXLQ::getMovingSpeed(const byte bID)
{
	return this->getWord(bID, DXL_MOVING_SPEED);
}

inline void DXLQ::getMovingSpeed(const byte bID[], const byte bIDLength, word wMovingSpeed[])
{
	this->getWord(bID, bIDLength, DXL_MOVING_SPEED, wMovingSpeed);
}


inline byte DXLQ::setMovingSpeed(const word wMovingSpeed)
{
	return this->setWord(DXL_MOVING_SPEED, wMovingSpeed);
}

inline byte DXLQ::setMovingSpeed(const byte bID, const word wMovingSpeed)
{
	return this->setWord(bID, DXL_MOVING_SPEED, wMovingSpeed);
}

inline byte DXLQ::setMovingSpeed(const byte bID[], const byte bIDLength, const word wMovingSpeed)
{
	return this->setWord(bID, bIDLength, DXL_MOVING_SPEED, wMovingSpeed);
}

inline byte DXLQ::setMovingSpeed(const byte bID[], const byte bIDLength, const word wMovingSpeed[])
{
	return this->setWord(bID, bIDLength, DXL_MOVING_SPEED, wMovingSpeed);
}


// DXL_TORQUE_LIMIT
inline word DXLQ::getTorqueLimit(const byte bID)
{
	return this->getWord(bID, DXL_TORQUE_LIMIT);
}

inline void DXLQ::getTorqueLimit(const byte bID[], const byte bIDLength, word wTorqueLimit[])
{
	this->getWord(bID, bIDLength, DXL_TORQUE_LIMIT, wTorqueLimit);
}


inline byte DXLQ::setTorqueLimit(const word wTorqueLimit)
{
	return this->setWord(DXL_TORQUE_LIMIT, wTorqueLimit);
}

inline byte DXLQ::setTorqueLimit(const byte bID, const word wTorqueLimit)
{
	return this->setWord(bID, DXL_TORQUE_LIMIT, wTorqueLimit);
}

inline byte DXLQ::setTorqueLimit(const byte bID[], const byte bIDLength, const word wTorqueLimit)
{
	return this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, wTorqueLimit);
}

inline byte DXLQ::setTorqueLimit(const byte bID[], const byte bIDLength, const word wTorqueLimit[])
{
	return this->setWord(bID, bIDLength, DXL_TORQUE_LIMIT, wTorqueLimit);
}


// DXL_PRESENT_POSITION
inline word DXLQ::getPresentPosition(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_POSITION);
}

inline void DXLQ::getPresentPosition(const byte bID[], const byte bIDLength, word wPresentPosition[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_POSITION, wPresentPosition);
}


// DXL_PRESENT_SPEED
inline word DXLQ::getPresentSpeed(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_SPEED);
}

inline void DXLQ::getPresentSpeed(const byte bID[], const byte bIDLength, word wPresentSpeed[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_SPEED, wPresentSpeed);
}


// DXL_PRESENT_LOAD
inline word DXLQ::getPresentLoad(const byte bID)
{
	return this->getWord(bID, DXL_PRESENT_LOAD);
}

inline void DXLQ::getPresentLoad(const byte bID[], const byte bIDLength, word wPresentLoad[])
{
	this->getWord(bID, bIDLength, DXL_PRESENT_LOAD, wPresentLoad);
}


// DXL_PRESENT_TEMPERATURE
inline byte DXLQ::getTemperature(byte bID)
{
	return this->getByte(bID, DXL_PRESENT_TEMPERATURE);
}

inline void DXLQ::getTemperature(const byte bID[], const byte bIDLength, byte bTemperature[])
{
	this->getByte(bID, bIDLength, DXL_PRESENT_TEMPERATURE, bTemperature);
}


// DXL_REGISTERED
inline byte DXLQ::getRegistered(byte bID)
{
	return this->getByte(bID, DXL_REGISTERED);
}

inline void DXLQ::getRegistered(const byte bID[], const byte bIDLength, byte bRegistered[])
{
	this->getByte(bID, bIDLength, DXL_REGISTERED, bRegistered);
}


// DXL_MOVING
inline byte DXLQ::getMoving(byte bID)
{
	return this->getByte(bID, DXL_MOVING);
}

inline void DXLQ::getMoving(const byte bID[], const byte bIDLength, byte bMoving[])
{
	this->getByte(bID, bIDLength, DXL_MOVING, bMoving);
}


// DXL_LOCK
inline byte DXLQ::getLock(const byte bID)
{
	return this->getByte(bID, DXL_LOCK);
}
	
inline void DXLQ::getLock(const byte bID[], const byte bIDLength, byte bLock[])
{
	this->getByte(bID, bIDLength, DXL_LOCK, bLock);
}


inline byte DXLQ::setLock(void)
{
	return this->setByte(DXL_LOCK, DXL_TRUE);
}

inline byte DXLQ::setLock(const byte bID)
{
	return this->setByte(bID, DXL_LOCK, DXL_TRUE);
}

inline byte DXLQ::setLock(const byte bID[], const byte bIDLength)
{
	return this->setByte(bID, bIDLength, DXL_LOCK, DXL_TRUE);
}


// DXL_PUNCH
inline word DXLQ::getPunch(const byte bID)
{
	return this->getWord(bID, DXL_PUNCH);
}

inline void DXLQ::getPunch(const byte bID[], const byte bIDLength, word wPunch[])
{
	this->getWord(bID, bIDLength, DXL_PUNCH, wPunch);
}


inline byte DXLQ::setPunch(const word wPunch)
{
	return this->setWord(DXL_PUNCH, DXL_MIN(wPunch, DXL_MAX_PUNCH));
}

inline byte DXLQ::setPunch(const byte bID, const word wPunch)
{
	return this->setWord(bID, DXL_PUNCH, DXL_MIN(wPunch, DXL_MAX_PUNCH));
}

inline byte DXLQ::setPunch(const byte bID[], const byte bIDLength, const word wPunch)
{
	return this->setWord(bID, bIDLength, DXL_PUNCH, DXL_MIN(wPunch, DXL_MAX_PUNCH));
}

byte DXLQ::setPunch(const byte bID[], const byte bIDLength, word wPunch[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		wPunch[i] = DXL_MIN(wPunch[i], DXL_MAX_PUNCH);
	}
	return this->setWord(bID, bIDLength, DXL_PUNCH, wPunch);
}


// DXL_CURRENT
inline word DXLQ::getCurrent(const byte bID)
{
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		return this->getWord(bID, DXL_CURRENT);
	}
	return DXL_INVALID_WORD;
}

inline void DXLQ::getCurrent(const byte bID[], const byte bIDLength, word wCurrent[])
{
	this->getWord(bID, bIDLength, DXL_CURRENT, wCurrent);
}


inline byte DXLQ::setCurrent(const byte bID, const word wCurrent)
{
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		return this->setWord(bID, DXL_CURRENT, DXL_MIN(wCurrent, DXL_MX_MAX_CURRENT));
	}
	return DXL_FAILURE;
}

byte DXLQ::setCurrent(const byte bID[], const byte bIDLength, const word wCurrent)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
	}
	return this->setWord(bID, bIDLength, DXL_CURRENT, DXL_MIN(wCurrent, DXL_MX_MAX_CURRENT));
}

byte DXLQ::setCurrent(const byte bID[], const byte bIDLength, word wCurrent[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
		wCurrent[i] = DXL_MIN(wCurrent[i], DXL_MX_MAX_CURRENT);
	}
	return this->setWord(bID, bIDLength, DXL_CURRENT, wCurrent);
}


// DXL_TORQUE_CONTROL_MODE_ENABLE
inline byte DXLQ::getTorqueControlEnable(const byte bID)
{
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		return this->getByte(bID, DXL_TORQUE_CONTROL_MODE_ENABLE);
	}
	return DXL_INVALID_BYTE;
}
	
inline void DXLQ::getTorqueControlEnable(const byte bID[], const byte bIDLength, byte bTorqueControlEnable[])
{
	this->getByte(bID, bIDLength, DXL_TORQUE_CONTROL_MODE_ENABLE, bTorqueControlEnable);
}


inline byte DXLQ::setTorqueControlEnable(const byte bID, const byte bTorqueControlEnable)
{
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		return this->setByte(bID, DXL_TORQUE_CONTROL_MODE_ENABLE, !!bTorqueControlEnable);
	}
	return DXL_FAILURE;
}

byte DXLQ::setTorqueControlEnable(const byte bID[], const byte bIDLength, const byte bTorqueControlEnable)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) == DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_TORQUE_CONTROL_MODE_ENABLE, !!bTorqueControlEnable);
}

byte DXLQ::setTorqueControlEnable(const byte bID[], const byte bIDLength, byte bTorqueControlEnable[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
		bTorqueControlEnable[i] = !!bTorqueControlEnable[i];
	}
	return this->setByte(bID, bIDLength, DXL_TORQUE_CONTROL_MODE_ENABLE, bTorqueControlEnable);
}


// DXL_GOAL_TORQUE
inline word DXLQ::getGoalTorque(const byte bID)
{
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		return this->getWord(bID, DXL_GOAL_TORQUE);
	}
	return DXL_INVALID_WORD;
}

inline void DXLQ::getGoalTorque(const byte bID[], const byte bIDLength, word wGoalTorque[])
{
	this->getWord(bID, bIDLength, DXL_GOAL_TORQUE, wGoalTorque);
}


inline byte DXLQ::setGoalTorque(const byte bID, const word wGoalTorque)
{
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		return this->setWord(bID, DXL_GOAL_TORQUE, DXL_MIN(wGoalTorque, DXL_MX_MAX_GOAL_TORQUE));
	}
	return DXL_FAILURE;
}

byte DXLQ::setGoalTorque(const byte bID[], const byte bIDLength, const word wGoalTorque)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
	}
	return this->setWord(bID, bIDLength, DXL_GOAL_TORQUE, DXL_MIN(wGoalTorque, DXL_MX_MAX_GOAL_TORQUE));
}

byte DXLQ::setGoalTorque(const byte bID[], const byte bIDLength, word wGoalTorque[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
		wGoalTorque[i] = DXL_MIN(wGoalTorque[i], DXL_MX_MAX_GOAL_TORQUE);
	}
	return this->setWord(bID, bIDLength, DXL_GOAL_TORQUE, wGoalTorque);
}


// DXL_GOAL_ACCELERATION
inline byte DXLQ::getGoalAcceleration(const byte bID)
{
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		return this->getByte(bID, DXL_GOAL_ACCELERATION);
	}
	return DXL_INVALID_BYTE;
}

inline void DXLQ::getGoalAcceleration(const byte bID[], const byte bIDLength, byte bGoalAcceleration[])
{
	this->getByte(bID, bIDLength, DXL_GOAL_ACCELERATION, bGoalAcceleration);
}


inline byte DXLQ::setGoalAcceleration(const byte bID, const byte bGoalAcceleration)
{
	if (this->getSeriesType(bID) == DXL_MX_SERIES_ADVANCED) {
		return this->setByte(bID, DXL_GOAL_ACCELERATION, DXL_MIN(bGoalAcceleration, DXL_MX_MAX_ACCELERATION));
	}
	return DXL_FAILURE;
}

byte DXLQ::setGoalAcceleration(const byte bID[], const byte bIDLength, const byte bGoalAcceleration)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
	}
	return this->setByte(bID, bIDLength, DXL_GOAL_ACCELERATION, DXL_MIN(bGoalAcceleration, DXL_MX_MAX_ACCELERATION));
}

byte DXLQ::setGoalAcceleration(const byte bID[], const byte bIDLength, byte bGoalAcceleration[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (bID[i] > DXL_MAX_ID || this->getSeriesType(bID[i]) != DXL_MX_SERIES_ADVANCED) {
			return DXL_FAILURE;
		}
		bGoalAcceleration[i] = DXL_MIN(bGoalAcceleration[i], DXL_MX_MAX_ACCELERATION);
	}
	return this->setByte(bID, bIDLength, DXL_GOAL_ACCELERATION, bGoalAcceleration);
}

#endif /* DXL_GETSET_H_ */