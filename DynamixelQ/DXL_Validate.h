/*
 *	DXL_Validate.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 4-12-15, modified: 4-23-15
 */

#ifndef DXL_VALIDATE_H_
#define DXL_VALIDATE_H_

inline DXL_BOOL DXLQ::isInit(const byte bID)
{
	return (bID <= DXL_MAX_ID && this->dxl_isActuatorID[bID]) ? DXL_TRUE : DXL_FALSE;
}

void DXLQ::isInit(const byte bID[], const byte bIDLength, DXL_BOOL bIsInit[])
{
	byte i;
	
	for (i = 0; i <= bIDLength; i++) {
		bIsInit[i] = this->isInit(bID[i]);
	}
}


inline DXL_BOOL DXLQ::checkID(const byte bID)
{
	word wModelNumber;
	
	if (this->dxl_beginCalled && bID <= DXL_MAX_ID) {
		if (this->dxl_isActuatorID[bID]) {
			if (this->doPing(bID) <= DXL_MAX_ID) {
				return DXL_TRUE;
			}
		} else if (this->doPing(bID) <= DXL_MAX_ID) {
			wModelNumber = this->getWord(bID, DXL_MODEL_NUMBER);
			if (wModelNumber != DXL_INVALID_WORD) {
				this->dxl_isActuatorID[bID] = DXL_TRUE;
				this->dxl_ModelNumber[bID] = wModelNumber;
				this->dxl_num_actuators_initialized++;
				return DXL_TRUE;
			}
		}
	}
	return DXL_FALSE;
}


inline DXL_SERIES DXLQ::getSeries(const byte bID)
{
	if (this->checkID(bID)) {
		switch(this->dxl_ModelNumber[bID]) {
			case DXL_AX12:
			case DXL_AX18:
			case DXL_AX12W:
				return DXL_AX_SERIES;
			case DXL_MX12W:
			case DXL_MX28:
			case DXL_MX64:
			case DXL_MX106:
				return DXL_MX_SERIES;
			default:
				return DXL_UNKNOWN_SERIES;
		}
	}
	return DXL_UNKNOWN_SERIES;
}

void DXLQ::getSeries(const byte bID[], const byte bIDLength, DXL_SERIES bSeries[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bSeries[i] = this->getSeries(bID[i]);
	}
}


inline DXL_SERIES_TYPE DXLQ::getSeriesType(const byte bID)
{
	if (this->checkID(bID)) {
		switch(this->dxl_ModelNumber[bID]) {
			case DXL_AX12:
			case DXL_AX18:
			case DXL_AX12W:
				return DXL_AX_SERIES_TYPE;
			case DXL_MX12W:
			case DXL_MX28:
				return DXL_MX_SERIES_BASIC;
			case DXL_MX64:
			case DXL_MX106:
				return DXL_MX_SERIES_ADVANCED;
			default:
				return DXL_UNKNOWN_SERIES_TYPE;
		}
	}
	return DXL_UNKNOWN_SERIES_TYPE;
}

void DXLQ::getSeriesType(const byte bID[], const byte bIDLength, DXL_SERIES_TYPE bSeriesType[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bSeriesType[i] = this->getSeriesType(bID[i]);
	}
}


/*
 *	Returns 1 if an address start location is valid and stores a byte or low or high
 *	byte of a word and 0 otherwise.
 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
 */
inline byte DXLQ::isByteAddressValid(const byte bID, const byte bAddress)
{
	if (bID <= DXL_MAX_ID && bAddress < DXL_NUM_ADDRESS) {
		switch(this->getSeriesType(bID)) {
			case DXL_AX_SERIES_TYPE:
				return ((bAddress >= DXL_MULTI_TURN_OFFSET && bAddress <= DXL_RESOLUTION_DIVIDER) || bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : (DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
			case DXL_MX_SERIES_BASIC:
				return (bAddress == DXL_CCW_COMPLIANCE_SLOPE || (bAddress > DXL_AX_NUM_ADDRESS && bAddress != DXL_GOAL_ACCELERATION)) ? DXL_FALSE : (DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
			case DXL_MX_SERIES_ADVANCED:
				return (bAddress == DXL_CCW_COMPLIANCE_SLOPE) ? DXL_FALSE : (DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
			default:
				return DXL_FALSE;
		}
	}
	return DXL_FALSE;
}


/*
 *	Returns 1 if an address start location is valid and stores a byte and 0 otherwise.
 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
 */
inline byte DXLQ::isByteAddress(const byte bID, const byte bAddress)
{
	if (bID <= DXL_MAX_ID && bAddress < DXL_NUM_ADDRESS) {
		switch(this->getSeriesType(bID)) {
			case DXL_AX_SERIES_TYPE:
				return (bAddress == DXL_RESOLUTION_DIVIDER || bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : (DXL_ADDRESS[bAddress] == DXL_BYTE_ADDRESS_TYPE);
			case DXL_MX_SERIES_BASIC:
				return (bAddress == DXL_CCW_COMPLIANCE_SLOPE || (bAddress > DXL_AX_NUM_ADDRESS && bAddress != DXL_GOAL_ACCELERATION)) ? DXL_FALSE : (DXL_ADDRESS[bAddress] == DXL_BYTE_ADDRESS_TYPE);
			case DXL_MX_SERIES_ADVANCED:
				return (bAddress == DXL_CCW_COMPLIANCE_SLOPE) ? DXL_FALSE : (DXL_ADDRESS[bAddress] == DXL_BYTE_ADDRESS_TYPE);
			default:
				return DXL_FALSE;
		}
	}
	return DXL_FALSE;
}

/*
 *	Returns 1 if an address start location is valid and stores a word and 0 otherwise.
 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
 */
inline byte DXLQ::isWordAddress(const byte bID, const byte bAddress)
{
	if (bID <= DXL_MAX_ID && bAddress < DXL_NUM_ADDRESS) {
		switch(this->getSeriesType(bID)) {
			case DXL_AX_SERIES_TYPE:
				return (bAddress == DXL_MULTI_TURN_OFFSET || bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : (DXL_ADDRESS[bAddress] == DXL_WORD_L_ADDRESS_TYPE);
			case DXL_MX_SERIES_BASIC:
				return (bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : (DXL_ADDRESS[bAddress] == DXL_WORD_L_ADDRESS_TYPE);
			case DXL_MX_SERIES_ADVANCED:
				return (DXL_ADDRESS[bAddress] == DXL_WORD_L_ADDRESS_TYPE);
			default:
				return DXL_FALSE;
		}
	}
	return DXL_FALSE;
}


inline byte DXLQ::isValidByte(const byte bData)
{
	return (bData != DXL_INVALID_BYTE);
}

inline void DXLQ::isValidByte(const byte bData[], const byte bDataLength, byte bValidByte[])
{
	byte i;
	
	for (i = 0; i < bDataLength; i++) {
		bValidByte[i] = (bData[i] != DXL_INVALID_BYTE);
	}
}

inline byte DXLQ::allValidByte(const byte bData[], const byte bDataLength)
{
	byte i;
	
	for (i = 0; i < bDataLength; i++) {
		if (bData[i] == DXL_INVALID_BYTE) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}


inline byte DXLQ::isValidWord(const word wData)
{
	return (wData != DXL_INVALID_WORD);
}

inline void DXLQ::isValidWord(const word wData[], const byte bDataLength, byte bValidWord[])
{
	byte i;
	
	for (i = 0; i < bDataLength; i++) {
		bValidWord[i] = (wData[i] != DXL_INVALID_WORD);
	}
}

inline byte DXLQ::allValidWord(const word wData[], const byte bDataLength)
{
	byte i;
	
	for (i = 0; i < bDataLength; i++) {
		if (wData[i] == DXL_INVALID_WORD) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}


inline byte DXLQ::isAddressWritable(const byte bID, const byte bAddress)
{
	if (bID <= DXL_MAX_ID && bAddress < DXL_NUM_ADDRESS) {
		switch(this->getSeriesType(bID)) {
			case DXL_AX_SERIES_TYPE:
				return (bAddress < DXL_ID || (bAddress >= DXL_PRESENT_POSITION && bAddress < DXL_LOCK) || bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : (DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
			case DXL_MX_SERIES_BASIC:
				return (bAddress < DXL_ID || bAddress == DXL_CCW_COMPLIANCE_SLOPE || (bAddress >= DXL_PRESENT_POSITION && bAddress < DXL_LOCK) || (bAddress > DXL_AX_NUM_ADDRESS && bAddress != DXL_GOAL_ACCELERATION)) ? DXL_FALSE : (DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
			case DXL_MX_SERIES_ADVANCED:
				return (bAddress < DXL_ID || bAddress == DXL_CCW_COMPLIANCE_SLOPE || (bAddress >= DXL_PRESENT_POSITION && bAddress < DXL_LOCK)) ? DXL_FALSE : (DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
			default:
				return DXL_FALSE;
		}
	}
	return DXL_FALSE;
}

inline void DXLQ::isAddressWritable(const byte bID, const byte bAddress[], const byte bNumAddress, byte bWritable[])
{
	byte i;
	
	for (i = 0; i < bNumAddress; i++) {
		bWritable[i] = this->isAddressWritable(bID, bAddress[i]);
	}
}

#endif /* DXL_VALIDATE_H_ */