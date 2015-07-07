/*
 *	Tosser.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 7-5-15, modified: 7-6-15
 */

#ifndef TOSSER_H_
#define TOSSER_H_

#include "usb.h"
#include "delay.h"

#define TOSSER_DATA_BUFFER_SIZE uint8(255)

#define TOSSER_COMMAND_PACKET_LENGTH uint8(5)
#define TOSSER_PACKET_HEADER uint8(0x51) // 81, Q

enum TOSSER_COMMAND{
	TOSSER_BEGIN = uint8(0x41),	// 65, A
	TOSSER_PAUSE = uint8(0x42), // 66, B
	TOSSER_RESET = uint8(0x43), // 67, C
	TOSSER_EXIT  = uint8(0x44)  // 68, D
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
		Board.blink(5e5);
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
		while (this->bTosserState != TOSSER_STOP) {
			// Read all available raw bytes from USB serial connection
			this->bNum = usbBytesAvailable();
			if (this->bNum == TOSSER_COMMAND_PACKET_LENGTH) {
				this->USBreadRAW(this->bData, this->bNum);
				this->readCommandPacket();
			}
			delay_us(100);
			
			if (this->bTosserState == TOSSER_RUN) {
				this->bResetBaudRateValue = this->bTosserBaudRateValue;
				Board.blink(1e4);
				
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
		#ifdef BOARD_H_
		Board.blink(5e5);
		#endif
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
					}
					break;
				case TOSSER_PAUSE:
					if (this->bData[3] == TOSSER_PAUSE) {
						this->bTosserState = TOSSER_WAIT;
					}
					break;
				case TOSSER_RESET:
					if (this->bData[3] == TOSSER_RESET) {
						this->bTosserBaudRateValue = this->bResetBaudRateValue;
						Dxl.begin(this->bTosserBaudRateValue);
						this->bTosserState = TOSSER_RUN;
					}
					break;
				case TOSSER_EXIT:
					if (this->bData[3] == TOSSER_EXIT) {
						this->bTosserState = TOSSER_STOP;
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
		delay_us(200);
		UserToPMABufferCopy(dat, 0xC0, datlen);
		_SetEPTxCount((uint8)1, datlen);
		_SetEPTxValid((uint8)1);
	}
	
	TOSSER_STATE bTosserState;
	uint8 bTosserBaudRateValue, bResetBaudRateValue;
	uint8 bNum, bData[TOSSER_DATA_BUFFER_SIZE];
};

// Instantiate Tosser object
TOSSER Tosser;

#endif /* TOSSER_H_ */