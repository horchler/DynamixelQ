/*
 *	DXL_Board.h
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 4-19-15, modified: 4-22-15
 */

#ifndef DXL_BOARD_H_
#define DXL_BOARD_H_

#define BOARD_MAX_RELOAD                   uint16(0xFFFF)

#define BOARD_LED_GPIO_BIT                              9
#define BOARD_BUTTON_GPIO_BIT                          15

#define BOARD_LED_TIMER_DEVICE                     TIMER4
#define BOARD_LED_TIMER_CHANNEL          uint8(TIMER_CH4)
#define BOARD_LED_TIMER_MIN_BLINK_PERIOD           20000U
#define BOARD_LED_TIMER_MAX_BLINKS            2147483647U
#define BOARD_LED_TIMER_MIN_ON_DURATION                1U

#define BOARD_LED_MAX_BRIGHTNESS           uint16(0xFFFF)

#define BOARD_LED_TIMER_MIN_FADE_PERIOD             1000U
#define BOARD_LED_MIN_BRIGHTNESS_STEP           uint16(1)

#define BOARD_BUTTON_DEBOUNCE_DELAY                 1000U

typedef enum BOARD_BOOL{
	BOARD_FALSE = 0,
	BOARD_TRUE
} BOARD_BOOL;

enum BOARD_LED_STATE{
	BOARD_LED_OFF = 0,
	BOARD_LED_ON
};

typedef enum BOARD_LED_MODE{
	BOARD_LED_BLINK_MODE = 0,
	BOARD_LED_FADE_MODE,
	BOARD_LED_UNKNOWN_MODE
} BOARD_LED_MODE;

enum BOARD_BUTTON_STATE{
	BOARD_BUTTON_OFF = 0,
	BOARD_BUTTON_ON
};

#define BOARD_MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define BOARD_MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })

class BOARD
{
public:
	BOARD(void);
	virtual ~BOARD(void);
	
	byte getLED(void);
	byte setLED(byte bLEDState=BOARD_LED_ON);
	byte toggleLED(void);
	
	void blink(uint32 ulMicroSecPeriod=1e6);
	void blink(uint32 ulMicroSecPeriod, uint32 ulMicroSecOnDuration);
	
	void blinkOnce(uint32 ulMicroSecPeriod=1e6);
	void blinkOnce(uint32 ulMicroSecPeriod, uint32 ulMicroSecOnDuration);
	
	void blinkNTimes(uint32 ulMicroSecPeriod=1e6, uint32 ulNTimes=1);
	void blinkNTimes(uint32 ulMicroSecPeriod, uint32 ulMicroSecOnDuration, uint32 ulNTimes);
	
	word getLEDBrightness(void);
	word setLEDBrightness(uint16 uOnBrightness=BOARD_LED_MAX_BRIGHTNESS);
	
	void fade(uint16 uOnBrightness=BOARD_LED_MAX_BRIGHTNESS, uint32 ulMicroSecPeriod=1e6);
	//void fade(uint16 uOnBrightness, uint32 ulMicroSecPeriod, uint32 ulMicroSecOnDuration);
	
	void fadeOnce(uint16 uOnBrightness=BOARD_LED_MAX_BRIGHTNESS, uint32 ulMicroSecPeriod=1e6);
	//void fadeOnce(uint16 uOnBrightness, uint32 ulMicroSecPeriod, uint32 ulMicroSecOnDuration);
	
	void fadeNTimes(uint16 uOnBrightness=BOARD_LED_MAX_BRIGHTNESS, uint32 ulMicroSecPeriod=1e6, uint32 ulNTimes=1);
	//void fadeNTimes(uint16 uOnBrightness, uint32 ulMicroSecPeriod, uint32 ulMicroSecOnDuration, uint32 ulNTimes);
	
	byte getButton(void);
	byte getButtonPress(void);
	
private:
	void initBlink(void);
	void initFade(void);
	
	void blinkSetup(uint32 ulMicroSecPeriod, voidFuncPtr handler);
	void fadeSetup(uint16 uOnBrightness, uint32 ulMicroSecPeriod, voidFuncPtr handler);
	
	byte initButton(void);
	
	BOARD_LED_MODE LEDTimerMode;
	
	BOARD_BOOL isInitButton;
};

#endif /* DXL_BOARD_H_ */