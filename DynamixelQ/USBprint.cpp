/*
 *	USBprint.cpp
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-24-14, modified: 10-3-14
 */

#include <stdio.h>
#include <string.h>
#include "ee_printf.h"
#include "systick.h"
#include "usb.h"

#define USBPRINT_BUFFER_SIZE (8*80)


int USBprint(const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE];
	int len;
	va_list args;
	
	va_start(args, fmt);
	len = vsprintf(buff, fmt, args);
	va_end(args);
	
	return (int)usbSendBytes((const uint8*)buff, len);
}

int USBprintInt(const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE];
	int len;
	va_list args;
	
	va_start(args, fmt);
	len = ee_vsprintf(buff, fmt, args);
	va_end(args);
	
	return (int)usbSendBytes((const uint8*)buff, len);
}

int USBprintStr(const char *str)
{
	return (int)usbSendBytes((const uint8*)str, strlen(str));
}

int USBprintRaw(const uint8 *dat, const int datlen)
{
	return (int)usbSendBytes(dat, datlen);
}