/*
 *	Tosser.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 7-5-15, modified: 7-9-15
 */

#ifndef TOSSER_H_
#define TOSSER_H_

#include "usb.h"

#define TOSSER_DATA_BUFFER_SIZE uint8(255)

#define TOSSER_PACKET_HEADER uint8(0x51) // 81, Q
#define TOSSER_COMMAND_PACKET_LENGTH uint8(5)
#define TOSSER_RETURN_PACKET_LENGTH uint8(4)

enum TOSSER_COMMAND{
	TOSSER_BEGIN  = uint8(0x41), // 65, A
	TOSSER_PAUSE  = uint8(0x42), // 66, B
	TOSSER_MICROS = uint8(0x43), // 67, C
	TOSSER_MILLIS = uint8(0x44), // 68, D
	TOSSER_STATUS = uint8(0x45), // 69, E
	TOSSER_BAUD   = uint8(0x46), // 70, E
	TOSSER_RESET  = uint8(0x47), // 71, G
	TOSSER_EXIT   = uint8(0x48)  // 72, H
};

typedef enum TOSSER_STATE{
	TOSSER_WAIT = 0,
	TOSSER_RUN,
	TOSSER_STOP
} TOSSER_STATE; 

#define TOSSER_DEFAULT_BAUD_RATE_VALUE DXL_DEFAULT_BAUD_RATE_VALUE

class TOSSER
{
public:
	TOSSER(void){
		#ifdef BOARD_H_
		Board.setLED(BOARD_LED_OFF);
		#endif
		this->bTosserState = TOSSER_WAIT;
	};
	virtual ~TOSSER(void){};
	
	void begin(void)
	{
		this->begin(TOSSER_DEFAULT_BAUD_RATE_VALUE);
	};
	
	void begin(const byte bBaudRateValue)
	{
		this->bResetBaudRateValue = bBaudRateValue;
		while (this->bTosserState != TOSSER_STOP) {
			// Read all available raw bytes from USB serial connection
			this->bNum = usbBytesAvailable();
			if (this->bNum == TOSSER_COMMAND_PACKET_LENGTH) {
				this->USBreadRAW(this->bData, this->bNum);
				this->readCommandPacket();
			}
			usDelay(100);
			
			if (this->bTosserState == TOSSER_RUN) {
				while (this->bTosserState == TOSSER_RUN) {
					// Read all available raw bytes from USB serial connection and write to Dynamixel bus
					this->bNum = usbBytesAvailable();
					this->USBreadRAW(this->bData, this->bNum);
					(this->bNum == TOSSER_COMMAND_PACKET_LENGTH) ? this->readCommandPacket() : Dxl.writeRaw(this->bData, this->bNum);
			
					// Read all available raw bytes from Dynamixel bus and write to USB serial connection
					this->bNum = Dxl.readRaw(this->bData, TOSSER_DATA_BUFFER_SIZE);
					this->USBprintRaw(this->bData, this->bNum);
				}
			}
		}
		this->bTosserState = TOSSER_WAIT;
	};
	
private:
	void readCommandPacket(void)
	{
		if (this->bData[0] == TOSSER_PACKET_HEADER && this->bData[1] == TOSSER_PACKET_HEADER && Dxl.isValidChecksum(this->bData, TOSSER_COMMAND_PACKET_LENGTH)) {
			switch(this->bData[2]) {
				case TOSSER_BEGIN:
					if (Dxl.isValidBaudRateValue(this->bData[3]) && this->bData[3] != bTosserBaudRateValue) {
						this->bTosserBaudRateValue = this->bData[3];
						Dxl.begin(this->bTosserBaudRateValue);
						this->bTosserState = TOSSER_RUN;
						#ifdef BOARD_H_
						Board.blink(1e4);
						#endif
					}
					break;
				case TOSSER_PAUSE:
					if (this->bData[3] == TOSSER_PAUSE) {
						this->bTosserState = TOSSER_WAIT;
						#ifdef BOARD_H_
						Board.blink(1e5);
						#endif
					}
					break;
				case TOSSER_MICROS:
					if (this->bData[3] == TOSSER_MICROS) {
						this->uTosserTime = microsec();
						this->bData[0] = TOSSER_PACKET_HEADER;
						this->bData[1] = TOSSER_PACKET_HEADER;
						this->bData[2] = TOSSER_MICROS;
						this->bData[3] = (this->uTosserTime & 0xFF);
						this->bData[4] = ((this->uTosserTime >> 8) & 0xFF);
						this->bData[5] = ((this->uTosserTime >> 16) & 0xFF);
						this->bData[6] = ((this->uTosserTime >> 24) & 0xFF);
						this->bData[7] = ~(this->bData[2]+this->bData[3]+this->bData[4]+this->bData[5]+this->bData[6]);
						this->bNum = TOSSER_RETURN_PACKET_LENGTH+4;
						this->USBprintRaw(this->bData, this->bNum);
					}
					break;
				case TOSSER_MILLIS:
					if (this->bData[3] == TOSSER_MILLIS) {
						this->uTosserTime = millisec();
						this->bData[0] = TOSSER_PACKET_HEADER;
						this->bData[1] = TOSSER_PACKET_HEADER;
						this->bData[2] = TOSSER_MILLIS;
						this->bData[3] = (this->uTosserTime & 0xFF);
						this->bData[4] = ((this->uTosserTime >> 8) & 0xFF);
						this->bData[5] = ((this->uTosserTime >> 16) & 0xFF);
						this->bData[6] = ((this->uTosserTime >> 24) & 0xFF);
						this->bData[7] = ~(this->bData[2]+this->bData[3]+this->bData[4]+this->bData[5]+this->bData[6]);
						this->bNum = TOSSER_RETURN_PACKET_LENGTH+4;
						this->USBprintRaw(this->bData, this->bNum);
					}
					break;
				case TOSSER_STATUS:
					if (this->bData[3] == TOSSER_STATUS) {
						this->bData[0] = TOSSER_PACKET_HEADER;
						this->bData[1] = TOSSER_PACKET_HEADER;
						this->bData[2] = TOSSER_STATUS;
						this->bData[3] = this->bTosserState;
						this->bData[4] = ~(this->bData[2]+this->bData[3]);
						this->bNum = TOSSER_RETURN_PACKET_LENGTH+1;
						this->USBprintRaw(this->bData, this->bNum);
					}
					break;
				case TOSSER_BAUD:
					if (this->bData[3] == TOSSER_BAUD) {
						this->bData[0] = TOSSER_PACKET_HEADER;
						this->bData[1] = TOSSER_PACKET_HEADER;
						this->bData[2] = TOSSER_BAUD;
						this->bData[3] = this->bTosserBaudRateValue;
						this->bData[4] = ~(this->bData[2]+this->bData[3]);
						this->bNum = TOSSER_RETURN_PACKET_LENGTH+1;
						this->USBprintRaw(this->bData, this->bNum);
					}
					break;
				case TOSSER_RESET:
					if (this->bData[3] == TOSSER_RESET) {
						this->bTosserBaudRateValue = this->bResetBaudRateValue;
						Dxl.begin(this->bTosserBaudRateValue);
						this->bTosserState = TOSSER_RUN;
						#ifdef BOARD_H_
						Board.blink(1e4);
						#endif
					}
					break;
				case TOSSER_EXIT:
					if (this->bData[3] == TOSSER_EXIT) {
						this->bTosserState = TOSSER_STOP;
						#ifdef BOARD_H_
						Board.setLED(BOARD_LED_OFF);
						#endif
					}
					break;
				default:
					break;
			}
		}
	}
	
	void USBreadRAW(uint8 dat[], const uint8 datlen)
	{
		uint8 i = 0;
		
		while (i < datlen) {
			i += usbReceiveBytes(&dat[i], datlen-i);
		}
	}
	
	inline void USBprintRaw(const uint8 *dat, const uint8 datlen) __attribute__((always_inline))
	{
		usDelay(200);
		UserToPMABufferCopy(dat, 0xC0, datlen);
		_SetEPTxCount((uint8)1, datlen);
		_SetEPTxValid((uint8)1);
	}
	
	TOSSER_STATE bTosserState;
	uint8 bTosserBaudRateValue, bResetBaudRateValue;
	uint8 bNum, bData[TOSSER_DATA_BUFFER_SIZE];
	uint32 uTosserTime;
};

// Instantiate Tosser object
TOSSER Tosser;

#endif /* TOSSER_H_ */