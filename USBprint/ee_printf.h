/*
 *	ee_printf.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-24-14, modified: 3-8-15
 */
 
#ifndef EE_PRINTF_H
#define EE_PRINTF_H
#if defined(__cplusplus)
extern "C" {
#endif

#include <stdarg.h>

int ee_vsprint(char *buf, const char *fmt, va_list args);
int ee_vsprintf(char *buf, const char *fmt, va_list args);

#if defined(__cplusplus)
}
#endif
#endif /* EE_PRINTF_H */