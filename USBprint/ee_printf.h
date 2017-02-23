/*
 *	ee_printf.h
 *	
 *	Author: Andrew D. Horchler, horchler @ gmail . com
 *	Created: 8-24-14, modified: 4-28-15
 */
 
#ifndef EE_PRINTF_H_
#define EE_PRINTF_H_
#if defined(__cplusplus)
extern "C" {
#endif

#include <stdarg.h>

int ee_vsprint(char *buf, const char *fmt, va_list args);
int ee_vsprintf(char *buf, const char *fmt, va_list args);

#if defined(__cplusplus)
}
#endif
#endif /* EE_PRINTF_H_ */