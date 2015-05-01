/*
 *	DXL_Validate.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 4-12-15, modified: 5-1-15
 */

#ifndef DXL_VALIDATE_H_
#define DXL_VALIDATE_H_

inline DXL_BOOL_TYPE DXL::isValidActuatorID(const byte bID)
{
	return DXL_BOOL_TYPE(bID <= DXL_MAX_ID);
}

DXL_BOOL_TYPE DXL::allValidActuatorID(const byte bID[], const byte bIDLength)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (!(this->isValidActuatorID(bID[i]))) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}


inline DXL_BOOL_TYPE DXL::isValidID(const byte bID)
{
	return DXL_BOOL_TYPE(this->isValidActuatorID(bID) || bID == BROADCAST_ID);
}

DXL_BOOL_TYPE DXL::allValidID(const byte bID[], const byte bIDLength)
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		if (!(this->isValidID(bID[i]))) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}


inline DXL_BOOL_TYPE DXL::isInit(const byte bID)
{
	return DXL_BOOL_TYPE(this->isValidActuatorID(bID) && this->dxl_isActuatorID[bID]);
}

void DXL::isInit(const byte bID[], const byte bIDLength, byte bIsInit[])
{
	byte i;
	
	for (i = 0; i <= bIDLength; i++) {
		bIsInit[i] = this->isInit(bID[i]);
	}
}


inline DXL_BOOL_TYPE DXL::checkID(const byte bID)
{
	word wModelNumber;
	
	if (this->dxl_beginCalled && this->isValidActuatorID(bID)) {
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


inline DXL_SERIES DXL::getSeries(const byte bID)
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

void DXL::getSeries(const byte bID[], const byte bIDLength, DXL_SERIES bSeries[])
{
	byte i;
	
	for (i = 0; i < bIDLength; i++) {
		bSeries[i] = this->getSeries(bID[i]);
	}
}


inline DXL_SERIES_TYPE DXL::getSeriesType(const byte bID)
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

void DXL::getSeriesType(const byte bID[], const byte bIDLength, DXL_SERIES_TYPE bSeriesType[])
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
inline DXL_BOOL_TYPE DXL::isByteAddressValid(const byte bID, const byte bAddress)
{
	if (bAddress < DXL_NUM_ADDRESS) {
		if (this->isValidID(bID)) {
			switch(this->getSeriesType(bID)) {
				case DXL_AX_SERIES_TYPE:
					return ((bAddress >= DXL_MULTI_TURN_OFFSET && bAddress <= DXL_RESOLUTION_DIVIDER) || bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
				case DXL_MX_SERIES_BASIC:
					return (bAddress == DXL_CCW_COMPLIANCE_SLOPE || (bAddress > DXL_AX_NUM_ADDRESS && bAddress != DXL_GOAL_ACCELERATION)) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
				case DXL_MX_SERIES_ADVANCED:
					return (bAddress == DXL_CCW_COMPLIANCE_SLOPE) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
				default:
					return DXL_FALSE;
			}
		} else if (bID == BROADCAST_ID) {
			return DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
		}
	}
	return DXL_FALSE;
}


/*
 *	Returns 1 if an address start location is valid and stores a byte and 0 otherwise.
 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
 */
inline DXL_BOOL_TYPE DXL::isByteAddress(const byte bID, const byte bAddress)
{
	if (bAddress < DXL_NUM_ADDRESS) {
		if (this->isValidActuatorID(bID)) {
			switch(this->getSeriesType(bID)) {
				case DXL_AX_SERIES_TYPE:
					return (bAddress == DXL_RESOLUTION_DIVIDER || bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] == DXL_BYTE_ADDRESS_TYPE);
				case DXL_MX_SERIES_BASIC:
					return (bAddress == DXL_CCW_COMPLIANCE_SLOPE || (bAddress > DXL_AX_NUM_ADDRESS && bAddress != DXL_GOAL_ACCELERATION)) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] == DXL_BYTE_ADDRESS_TYPE);
				case DXL_MX_SERIES_ADVANCED:
					return (bAddress == DXL_CCW_COMPLIANCE_SLOPE) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] == DXL_BYTE_ADDRESS_TYPE);
				default:
					return DXL_FALSE;
			}
		} else if (bID == BROADCAST_ID) {
			return DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] == DXL_BYTE_ADDRESS_TYPE);
		}
	}
	return DXL_FALSE;
}

/*
 *	Returns 1 if an address start location is valid and stores a word and 0 otherwise.
 *	http://support.robotis.com/en/product/dynamixel/mx_series/mx-64.htm#Control_Table
 */
inline DXL_BOOL_TYPE DXL::isWordAddress(const byte bID, const byte bAddress)
{
	if (bAddress < DXL_NUM_ADDRESS) {
		if (this->isValidActuatorID(bID)) {
			switch(this->getSeriesType(bID)) {
				case DXL_AX_SERIES_TYPE:
					return (bAddress == DXL_MULTI_TURN_OFFSET || bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] == DXL_WORD_L_ADDRESS_TYPE);
				case DXL_MX_SERIES_BASIC:
					return (bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] == DXL_WORD_L_ADDRESS_TYPE);
				case DXL_MX_SERIES_ADVANCED:
					return DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] == DXL_WORD_L_ADDRESS_TYPE);
				default:
					return DXL_FALSE;
			}
		} else if (bID == BROADCAST_ID) {
			return DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] == DXL_WORD_L_ADDRESS_TYPE);
		}
	}
	return DXL_FALSE;
}


inline DXL_BOOL_TYPE DXL::isValidByte(const byte bData)
{
	return DXL_BOOL_TYPE(bData != DXL_INVALID_BYTE);
}

inline void DXL::isValidByte(const byte bData[], const byte bDataLength, byte bValidByte[])
{
	byte i;
	
	for (i = 0; i < bDataLength; i++) {
		bValidByte[i] = (bData[i] != DXL_INVALID_BYTE);
	}
}

inline DXL_BOOL_TYPE DXL::allValidByte(const byte bData[], const byte bDataLength)
{
	byte i;
	
	for (i = 0; i < bDataLength; i++) {
		if (bData[i] == DXL_INVALID_BYTE) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}


inline DXL_BOOL_TYPE DXL::isValidWord(const word wData)
{
	return DXL_BOOL_TYPE(wData != DXL_INVALID_WORD);
}

inline void DXL::isValidWord(const word wData[], const byte bDataLength, byte bValidWord[])
{
	byte i;
	
	for (i = 0; i < bDataLength; i++) {
		bValidWord[i] = (wData[i] != DXL_INVALID_WORD);
	}
}

inline DXL_BOOL_TYPE DXL::allValidWord(const word wData[], const byte bDataLength)
{
	byte i;
	
	for (i = 0; i < bDataLength; i++) {
		if (wData[i] == DXL_INVALID_WORD) {
			return DXL_FALSE;
		}
	}
	return DXL_TRUE;
}


inline DXL_BOOL_TYPE DXL::isAddressWritable(const byte bID, const byte bAddress)
{
	if (bAddress < DXL_NUM_ADDRESS) {
		if (this->isValidActuatorID(bID)) {
			switch(this->getSeriesType(bID)) {
				case DXL_AX_SERIES_TYPE:
					return (bAddress < DXL_ID || (bAddress >= DXL_PRESENT_POSITION && bAddress < DXL_LOCK) || bAddress > DXL_AX_NUM_ADDRESS) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
				case DXL_MX_SERIES_BASIC:
					return (bAddress < DXL_ID || bAddress == DXL_CCW_COMPLIANCE_SLOPE || (bAddress >= DXL_PRESENT_POSITION && bAddress < DXL_LOCK) || (bAddress > DXL_AX_NUM_ADDRESS && bAddress != DXL_GOAL_ACCELERATION)) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
				case DXL_MX_SERIES_ADVANCED:
					return (bAddress < DXL_ID || bAddress == DXL_CCW_COMPLIANCE_SLOPE || (bAddress >= DXL_PRESENT_POSITION && bAddress < DXL_LOCK)) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
				default:
					return DXL_FALSE;
			}
		} else if (bID == BROADCAST_ID) {
			return (bAddress < DXL_ID || (bAddress >= DXL_PRESENT_POSITION && bAddress < DXL_LOCK)) ? DXL_FALSE : DXL_BOOL_TYPE(DXL_ADDRESS[bAddress] != DXL_UNDEFINED_ADDRESS_TYPE);
		}
	}
	return DXL_FALSE;
}

inline void DXL::isAddressWritable(const byte bID, const byte bAddress[], const byte bNumAddress, byte bWritable[])
{
	byte i;
	
	for (i = 0; i < bNumAddress; i++) {
		bWritable[i] = this->isAddressWritable(bID, bAddress[i]);
	}
}

#endif /* DXL_VALIDATE_H_ */