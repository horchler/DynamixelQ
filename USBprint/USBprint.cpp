/*
 *	USBprint.cpp
 *  
 *	Author: Andrew D. Horchler, horchler @ gmail . com
 *	Created: 8-24-14, modified: 3-22-15
 */

#include <stdarg.h>
#include <stdio.h>
#include "ee_printf.h"
#include "USBprint.h"

int USBsprint(char *str, size_t n, const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE+1];
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = vsniprintf(buff, USBPRINT_BUFFER_SIZE+1, fmt, args);
	va_end(args);
	
	len = (len < USBPRINT_BUFFER_SIZE) ? len : USBPRINT_BUFFER_SIZE;
	len = (len < (int)n) ? len : (int)n;
	strncpy(str, buff, len);
	return len;
}

int USBprint(const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE+1];
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = vsniprintf(buff, USBPRINT_BUFFER_SIZE+1, fmt, args);
	va_end(args);
	
	if (len > 0) {
		len = (len < USBPRINT_BUFFER_SIZE) ? len : USBPRINT_BUFFER_SIZE;
		usbSendBytes((const uint8*)buff, len);
	}
	return len;
}

int USBprintln(const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE+1];
	const char *returnStr = "\r\n";
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = vsniprintf(buff, USBPRINT_BUFFER_SIZE-1, fmt, args)+2;
	va_end(args);
	
	strcat(buff, returnStr);
	len = (len < USBPRINT_BUFFER_SIZE) ? len : USBPRINT_BUFFER_SIZE;
	usbSendBytes((const uint8*)buff, len);
	return len;
}

int USBsprintf(char *str, size_t n, const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE+1];
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = vsnprintf(buff, USBPRINT_BUFFER_SIZE+1, fmt, args);
	va_end(args);
	
	len = (len < USBPRINT_BUFFER_SIZE) ? len : USBPRINT_BUFFER_SIZE;
	len = (len < (int)n) ? len : (int)n;
	strncpy(str, buff, len);
	return len;
}

int USBprintf(const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE+1];
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = vsnprintf(buff, USBPRINT_BUFFER_SIZE+1, fmt, args);
	va_end(args);
	
	if (len > 0) {
		len = (len < USBPRINT_BUFFER_SIZE) ? len : USBPRINT_BUFFER_SIZE;
		usbSendBytes((const uint8*)buff, len);
	}
	return len;
}

int USBprintfln(const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE+1];
	const char *returnStr = "\r\n";
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = vsnprintf(buff, USBPRINT_BUFFER_SIZE-1, fmt, args);
	va_end(args);
	
	strcat(buff, returnStr);
	len = (len < USBPRINT_BUFFER_SIZE) ? len : USBPRINT_BUFFER_SIZE;
	usbSendBytes((const uint8*)buff, len);
	return len;
}

int USBsprintLite(char *str, const char *fmt, ...)
{
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
    
    va_start(args, fmt);
    len = ee_vsprint(str, fmt, args);
	va_end(args);
	
	return len;
}

int USBprintLite(const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE+1];
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = ee_vsprint(buff, fmt, args);
	va_end(args);
	
	usbSendBytes((const uint8*)buff, len);
	return len;
}

int USBsprintfLite(char *str, const char *fmt, ...)
{
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = ee_vsprintf(str, fmt, args);
	va_end(args);
	
	return len;
}

int USBprintfLite(const char *fmt, ...)
{
	char buff[USBPRINT_BUFFER_SIZE+1];
	int len;
	va_list args;
	
	if (!USBprintReady()) {
        return 0;
    }
	
	va_start(args, fmt);
	len = ee_vsprintf(buff, fmt, args);
	va_end(args);
	
	usbSendBytes((const uint8*)buff, len);
	return len;
}