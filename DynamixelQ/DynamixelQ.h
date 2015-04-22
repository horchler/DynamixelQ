/*
 *	DynamixelQ.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 4-4-15, modified: 4-22-15
 */

#ifndef DYNAMIXELQ_H_
#define DYNAMIXELQ_H_

#ifndef DXLQ_H_
	#include "DXLQ.h"
	#include "DXL_Utils.h"
	#include "DXL_GetSet.h"
	
	// Instantiate DynamixelQ object
	DXLQ Dxl;
#endif

#ifndef DXL_BOARD_H_
	#include "DXL_Board.h"
	
	// Instantiate Board object
	BOARD Board;
#endif

#endif