/*
 *	Board.cpp
 *	
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 4-19-15, modified: 4-30-15
 */

#include <math.h>
#include "CM904.h"
#include "delay.h"
#include "gpio.h"
#include "timer.h"
#include "Board.h"

static uint32 LEDTimerDuration;
static uint32 LEDTimerOffDuration;
static uint32 LEDTimerOnDuration;

static uint32 LEDTimerBlinkNTimes;

static float LEDTimerBrightness;
static float LEDTimerOnBrightness;

static float LEDTimerBrightnessSteps;
static float LEDTimerBrightnessStepSize;

static byte bFadeDirection = BOARD_TRUE;

static uint32 LEDTimerFadeNTimes;

BOARD::BOARD(void)
{	
	this->LEDTimerMode = BOARD_LED_UNKNOWN_MODE;
	
	this->isInitButton = BOARD_FALSE;
}
BOARD::~BOARD(void) {
}


void disableBlink(void)
{
	timer_detach_interrupt(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL);
    timer_cc_disable(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL);
}

void disableFade(void)
{
	timer_disable_irq(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL);
}


void BOARD::initBlink(void)
{
	if (this->LEDTimerMode != BOARD_LED_BLINK_MODE) {
		gpio_set_mode(GPIOB, BOARD_LED_GPIO_BIT, GPIO_OUTPUT_PP);
		this->LEDTimerMode = BOARD_LED_BLINK_MODE;
	}
	disableBlink();
}

void BOARD::initFade(void)
{
	if (this->LEDTimerMode != BOARD_LED_FADE_MODE) {
		gpio_set_mode(GPIOB, BOARD_LED_GPIO_BIT, GPIO_AF_OUTPUT_PP);
		disableBlink();
		this->LEDTimerMode = BOARD_LED_FADE_MODE;
	} else {
		disableFade();
	}
	timer_oc_set_mode(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL, TIMER_OC_MODE_PWM_1, TIMER_OC_PE);
    timer_cc_enable(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL);
}


uint16 setTimerPeriod(const uint32 ulMicroSecTimerPeriod)
{
	uint16 prescaler, uOverflow;
	uint32 period_cyc;
	
	period_cyc = ulMicroSecTimerPeriod*CYCLES_PER_MICROSECOND;
    prescaler = period_cyc/BOARD_MAX_RELOAD;
	timer_set_prescaler(BOARD_LED_TIMER_DEVICE, prescaler);
	uOverflow = (uint16)round(period_cyc/(prescaler+1U));
	timer_set_reload(BOARD_LED_TIMER_DEVICE, uOverflow);
	return uOverflow;
}


void BOARD::blinkSetup(const uint32 ulMicroSecPeriod, voidFuncPtr handler)
{
	uint16 uOverflow;
	
	this->initBlink();
	
	timer_pause(BOARD_LED_TIMER_DEVICE);
	uOverflow = setTimerPeriod(ulMicroSecPeriod);
    timer_set_compare(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL, BOARD_MIN(1, uOverflow));
    timer_attach_interrupt(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL, handler);
    timer_generate_update(BOARD_LED_TIMER_DEVICE);
    timer_set_count(BOARD_LED_TIMER_DEVICE, BOARD_MIN(2, uOverflow));
    timer_resume(BOARD_LED_TIMER_DEVICE);
}

void BOARD::fadeSetup(const uint16 uOnBrightness, const uint32 ulMicroSecPeriod, voidFuncPtr handler)
{
	uint16 uOverflow;
	
	this->initFade();
	
	LEDTimerOnBrightness = BOARD_MIN(uOnBrightness, BOARD_LED_MAX_BRIGHTNESS);
	LEDTimerBrightness = (this->getLED()) ? (float)uOnBrightness : 0.0;
	LEDTimerBrightnessSteps = ((float)ulMicroSecPeriod)/(2.0*((float)BOARD_LED_TIMER_MIN_FADE_PERIOD));
	LEDTimerBrightnessStepSize = ((float)uOnBrightness)/floor(LEDTimerBrightnessSteps);
	
	timer_pause(BOARD_LED_TIMER_DEVICE);
	uOverflow = setTimerPeriod(BOARD_LED_TIMER_MIN_FADE_PERIOD);
	timer_set_compare(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL, BOARD_MIN(1, uOverflow));
	timer_attach_interrupt(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL, handler);
	timer_generate_update(BOARD_LED_TIMER_DEVICE);
    timer_set_count(BOARD_LED_TIMER_DEVICE, BOARD_MIN(2, uOverflow));
    timer_resume(BOARD_LED_TIMER_DEVICE);
}


void blinkLEDHandler(void)
{
	gpio_toggle_bit(GPIOB, BOARD_LED_GPIO_BIT);
}

void blinkLEDDutyCycleHandler(void)
{
	blinkLEDHandler();
	setTimerPeriod((LEDTimerDuration == LEDTimerOnDuration)  ? LEDTimerOffDuration : LEDTimerOnDuration);
}

void blinkLEDNTimesHandler(void)
{
	blinkLEDHandler();
	if (--LEDTimerBlinkNTimes == 0) {
		disableBlink();
	}
}

void blinkLEDNTimesDutyCycleHandler(void)
{
	blinkLEDDutyCycleHandler();
	if (--LEDTimerBlinkNTimes == 0) {
		disableBlink();
	}
}

void fadeLEDHandler(void)
{	
	LEDTimerBrightness += (bFadeDirection ? LEDTimerBrightnessStepSize : -LEDTimerBrightnessStepSize);
	if (LEDTimerBrightness <= 0) {
		LEDTimerBrightness = 0.0;
		bFadeDirection = !bFadeDirection;
	} else if (LEDTimerBrightness > LEDTimerOnBrightness) {
		LEDTimerBrightness = LEDTimerOnBrightness;
		bFadeDirection = !bFadeDirection;
	}
    timer_set_compare(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL, BOARD_LED_MAX_BRIGHTNESS-(uint16)LEDTimerBrightness);
}
/*
void fadeLEDDutyCycleHandler(void)
{

}
*/
void fadeLEDNTimesHandler(void)
{
	LEDTimerBrightness += (bFadeDirection ? LEDTimerBrightnessStepSize : -LEDTimerBrightnessStepSize);
	if (LEDTimerBrightness <= 0) {
		LEDTimerBrightness = 0.0;
		bFadeDirection = !bFadeDirection;
		LEDTimerFadeNTimes--;
	} else if (LEDTimerBrightness > LEDTimerOnBrightness) {
		LEDTimerBrightness = LEDTimerOnBrightness;
		bFadeDirection = !bFadeDirection;
		LEDTimerFadeNTimes--;
	}
    timer_set_compare(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL, BOARD_LED_MAX_BRIGHTNESS-(uint16)LEDTimerBrightness);
	if (LEDTimerFadeNTimes == 0) {
		disableFade();
	}
}
/*
void fadeLEDNTimesDutyCycleHandler(void)
{
	fadeLEDDutyCycleHandler();
	if (--LEDTimerFadeNTimes == 0) {
		disableFade();
	}
}
*/

byte BOARD::getLED(void)
{
	return !gpio_read_bit(GPIOB, BOARD_LED_GPIO_BIT);
}

byte BOARD::setLED(const byte bLEDState)
{
	this->initBlink();
	gpio_write_bit(GPIOB, BOARD_LED_GPIO_BIT, !bLEDState);
	return !!bLEDState;
}

byte BOARD::toggleLED(void)
{
	this->initBlink();
	blinkLEDHandler();
	return this->getLED();
}


void BOARD::blink(const uint32 ulMicroSecPeriod)
{
	this->blinkSetup(BOARD_MAX(ulMicroSecPeriod/2, BOARD_LED_TIMER_MIN_BLINK_PERIOD), blinkLEDHandler);
}


void BOARD::blink(const uint32 ulMicroSecPeriod, const uint32 ulMicroSecOnDuration)
{	
	LEDTimerOnDuration = BOARD_MAX(ulMicroSecOnDuration, BOARD_LED_TIMER_MIN_ON_DURATION);
	LEDTimerOffDuration = BOARD_MAX(BOARD_MAX(ulMicroSecPeriod, BOARD_LED_TIMER_MIN_BLINK_PERIOD)-LEDTimerOnDuration, BOARD_LED_TIMER_MIN_ON_DURATION);
	LEDTimerDuration = (this->getLED()) ? LEDTimerOffDuration : LEDTimerOnDuration;
	this->blinkSetup(LEDTimerDuration, blinkLEDDutyCycleHandler);
}


void BOARD::blinkOnce(const uint32 ulMicroSecPeriod)
{
	this->blinkNTimes(ulMicroSecPeriod, 1);
}

void BOARD::blinkOnce(const uint32 ulMicroSecPeriod, const uint32 ulMicroSecOnDuration)
{
	this->blinkNTimes(ulMicroSecPeriod, ulMicroSecOnDuration, 1);
}


void BOARD::blinkNTimes(const uint32 ulMicroSecPeriod, const uint32 ulNTimes)
{	
	if (ulNTimes > 0) {
		LEDTimerBlinkNTimes = 2*BOARD_MIN(ulNTimes, BOARD_LED_TIMER_MAX_BLINKS);
		this->blinkSetup(BOARD_MAX((ulNTimes == 1) ? ulMicroSecPeriod : ulMicroSecPeriod/2, BOARD_LED_TIMER_MIN_BLINK_PERIOD), blinkLEDNTimesHandler);
	}
}

void BOARD::blinkNTimes(const uint32 ulMicroSecPeriod, const uint32 ulMicroSecOnDuration, const uint32 ulNTimes)
{	
	if (ulNTimes > 0) {
		LEDTimerOnDuration = BOARD_MAX(ulMicroSecOnDuration, BOARD_LED_TIMER_MIN_ON_DURATION);
		LEDTimerOffDuration = BOARD_MAX(BOARD_MAX(ulMicroSecPeriod, BOARD_LED_TIMER_MIN_BLINK_PERIOD)-LEDTimerOnDuration, BOARD_LED_TIMER_MIN_ON_DURATION);
		LEDTimerDuration = (this->getLED()) ? LEDTimerOffDuration : LEDTimerOnDuration;
		LEDTimerBlinkNTimes = 2*BOARD_MIN(ulNTimes, BOARD_LED_TIMER_MAX_BLINKS);
		this->blinkSetup(LEDTimerDuration, blinkLEDNTimesDutyCycleHandler);
	}
}


word BOARD::getLEDBrightness(void)
{
	return BOARD_LED_MAX_BRIGHTNESS-timer_get_compare(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL);
}

word BOARD::setLEDBrightness(const uint16 uOnBrightness)
{
	this->initFade();
	timer_set_compare(BOARD_LED_TIMER_DEVICE, BOARD_LED_TIMER_CHANNEL, BOARD_LED_MAX_BRIGHTNESS-uOnBrightness);
	return uOnBrightness;
}


void BOARD::fade(const uint16 uOnBrightness, const uint32 ulMicroSecPeriod)
{
	if (uOnBrightness > 0) {
		this->fadeSetup(uOnBrightness, BOARD_MAX(ulMicroSecPeriod/2, BOARD_LED_TIMER_MIN_BLINK_PERIOD), fadeLEDHandler);
	}
}
/*
void BOARD::fade(const uint16 uOnBrightness, const uint32 ulMicroSecPeriod, const uint32 ulMicroSecOnDuration)
{
	if (uOnBrightness > 0) {
		this->fadeSetup(uOnBrightness, ulMicroSecPeriod, fadeLEDHandler);
	}
}
*/

void BOARD::fadeOnce(const uint16 uOnBrightness, const uint32 ulMicroSecPeriod)
{
	this->fadeNTimes(uOnBrightness, ulMicroSecPeriod, 1);
}
/*
void BOARD::fadeOnce(const uint16 uOnBrightness, const uint32 ulMicroSecPeriod, const uint32 ulMicroSecOnDuration)
{
	this->fadeNTimes(uOnBrightness, ulMicroSecPeriod, ulMicroSecOnDuration, 1);
}
*/

void BOARD::fadeNTimes(const uint16 uOnBrightness, const uint32 ulMicroSecPeriod, const uint32 ulNTimes)
{
	if (uOnBrightness > 0 && ulNTimes > 0) {
		LEDTimerFadeNTimes = 2*BOARD_MIN(ulNTimes, BOARD_LED_TIMER_MAX_BLINKS);
		this->fadeSetup(uOnBrightness, (ulNTimes == 1) ? ulMicroSecPeriod : ulMicroSecPeriod/2, fadeLEDNTimesHandler);
	}
}
/*
void BOARD::fadeNTimes(const uint16 uOnBrightness, const uint32 ulMicroSecPeriod, const uint32 ulMicroSecOnDuration, const uint32 ulNTimes)
{
	if (uOnBrightness > 0 && ulNTimes > 0) {
		LEDTimerOffDuration = BOARD_MAX(ulMicroSecPeriod-BOARD_MIN(ulMicroSecOnDuration, ulMicroSecPeriod), BOARD_LED_TIMER_MIN_BLINK_PERIOD);
		LEDTimerOnDuration = BOARD_MAX(ulMicroSecOnDuration, BOARD_LED_TIMER_MIN_BLINK_PERIOD);
		LEDTimerFadeNTimes = 2*BOARD_MIN(ulNTimes, BOARD_LED_TIMER_MAX_BLINKS);
		this->fadeSetup(uOnBrightness, (this->getLED()) ? LEDTimerOnDuration : LEDTimerOffDuration, fadeLEDNTimesDutyCycleHandler);
	}
}
*/

byte BOARD::initButton(void)
{
	if (!isInitButton) {
		gpio_set_mode(GPIOC, BOARD_BUTTON_GPIO_BIT, GPIO_INPUT_PD);
		isInitButton = BOARD_TRUE;
	}
	return isInitButton;
}


byte BOARD::getButton(void)
{
	this->initButton();
	return gpio_read_bit(GPIOC, BOARD_BUTTON_GPIO_BIT) ? BOARD_BUTTON_ON : BOARD_BUTTON_OFF;
}


byte BOARD::getButtonPress(void)
{
	this->initButton();
	if (gpio_read_bit(GPIOC, BOARD_BUTTON_GPIO_BIT)) {
		delay_us(BOARD_BUTTON_DEBOUNCE_DELAY);
		while (gpio_read_bit(GPIOC, BOARD_BUTTON_GPIO_BIT));
		return BOARD_TRUE;
	}
	return BOARD_FALSE;
}