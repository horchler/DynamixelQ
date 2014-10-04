/*
 *	USBprint.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-24-14, modified: 10-3-14
 */
 
#ifndef USBPRINT_H
#define USBPRINT_H


#define USBprintf USBprint

/*
 *	Fast general print function to replace SerialUSB.print(). Note that this function
 *	requires a considerable amount of memory to support floating-point (12,112 bytes,
 *	about 10% of the maximum binary size of OpenCM9.04).
 */
int USBprint(const char *fmt, ...);

/*
 *	Fast integer-only print function using ee_vsprintf() to replace SerialUSB.print().
 */
int USBprintInt(const char *fmt, ...);

/*
 *	Fast string-only print function to replace SerialUSB.print().
 */
int USBprintStr(const char *str);

/*
 *	Print array of raw uint8 bytes of given length.
 */
int USBprintRaw(const uint8 *dat, int datlen);


#endif /* USBPRINT_H */