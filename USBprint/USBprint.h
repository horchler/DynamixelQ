/*
 *	USBprint.h
 *	
 *	Author: Andrew D. Horchler, horchler @ gmail . com
 *	Created: 8-24-14, modified: 7-3-15
 */
 
#ifndef USBPRINT_H_
#define USBPRINT_H_

#include <string.h>
#include "delay.h"
#include "usb.h"

#ifndef USBPRINT_BUFFER_SIZE
	#define USBPRINT_BUFFER_SIZE (8*80)
#endif

/*
 *  Return 1 if USB serial is connected and configured, 0 otherwise.
 */
inline int USBprintReady() __attribute__((always_inline));
inline int USBprintReady()
{
	return usbIsConnected() && usbIsConfigured();
}

/*
 *	Fast general print functions without floating-point support using vsniprintf to
 *	replace SerialUSB.print(). These functions require about 7,000 bytes. The number of
 *	bytes written is returned.
 */
int USBprint(const char *fmt, ...);
int USBprintln(const char *fmt, ...);
int USBsprint(char *str, size_t n, const char *fmt, ...);

/*
 *	Fast general print functions using vsnprintf to replace SerialUSB.print(). These
 *	functions require a considerable amount of memory to support floating-point: about 
 *	17,200 bytes. The number of bytes written is returned.
 */
int USBprintf(const char *fmt, ...);
int USBprintfln(const char *fmt, ...);
int USBsprintf(char *str, size_t n, const char *fmt, ...);

/*
 *	Fast print functions using ee_vsprint() to replace SerialUSB.print(). These functions
 *  use much less memory than USBprint: about 1,700 bytes. Not all format specifications
 *	are supported. The number of bytes written is returned.
 */
int USBprintLite(const char *fmt, ...);
int USBsprintLite(char *str, const char *fmt, ...);

/*
 *	Fast print functions using ee_vsprintf() to replace SerialUSB.print(). These functions
 *  use less memory than USBprintf: about 14,900 bytes. Not all format specifications
 *	are supported. The number of bytes written is returned.
 */
int USBprintfLite(const char *fmt, ...);
int USBsprintfLite(char *str, const char *fmt, ...);

/*
 *	Fast string-only print function to replace SerialUSB.print(). This very lightweight
 *  function only supports character string inputs. The number of bytes written is
 *	returned.
 */
inline int USBprintStr(const char *str)
{
	int len;
	
	len = strlen(str);
	if (USBprintReady() && len > 0) {
		usbSendBytes((const uint8*)str, len);
		return len;
	} else {
		return 0;
	}
}

/*
 *	Print raw uint8 byte. This low-level function only supports character input that has
 *	already been converted to raw unsigned 8-bit data. The number of bytes successfully
 *	written is returned.
 */
inline int USBprintRaw(const uint8 dat)
{
	if (USBprintReady()) {
		usbSendBytes(&dat, 1);
		return 1;
	} else {
		return 0;
	}
}

/*
 *	Print array of raw uint8 bytes of given length. This low-level function only supports
 *	character string inputs that have already been converted to raw unsigned 8-bit data. 
 *	The number of bytes successfully written is returned.
 */
inline int USBprintRaw(const uint8 *dat, const int datlen)
{
	if (USBprintReady() && datlen > 0) {
		usbSendBytes(dat, datlen);
		return datlen;
	} else {
		return 0;
	}
}

inline void _USBprintRaw(const uint8 dat)
{
	delay_us(200);
	UserToPMABufferCopy(&dat, 0xC0, 1);
	_SetEPTxCount((uint8)1, 1);
	_SetEPTxValid((uint8)1);
}

inline void _USBprintRaw(const uint8 *dat, const int datlen)
{
	delay_us(200);
	UserToPMABufferCopy(dat, 0xC0, datlen);
	_SetEPTxCount((uint8)1, datlen);
	_SetEPTxValid((uint8)1);
}

#endif /* USBPRINT_H_ */