/*
 *	ee_printf.c
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 8-24-14, modified: 9-6-14
 *
 *
 *	Based on: barebones/ee_printf.c
 *	Copyright (C) 2002 Michael Ringgaard. All rights reserved.
 *
 *		Redistribution and use in source and binary forms, with or without
 *		modification, are permitted provided that the following conditions
 *		are met:
 *
 *		1. Redistributions of source code must retain the above copyright 
 *		   notice, this list of conditions and the following disclaimer.  
 *		2. Redistributions in binary form must reproduce the above copyright
 *		   notice, this list of conditions and the following disclaimer in the
 *		   documentation and/or other materials provided with the distribution.  
 *		3. Neither the name of the project nor the names of its contributors
 *		   may be used to endorse or promote products derived from this software
 *		   without specific prior written permission. 
 *
 *		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *		ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *		IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *		ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 *		FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *		DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *		OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *		HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *		LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *		OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 *		SUCH DAMAGE.
 */
 
#include <stdarg.h>

#define USBPRINT_BUFFER_SIZE (8*80)
#define USBPRINT_NUM_INTERVAL_TIMERS (32+4)

#define ZEROPAD  	(1<<0)	/* Pad with zero */
#define SIGN    	(1<<1)	/* Unsigned/signed long */
#define PLUS    	(1<<2)	/* Show plus */
#define SPACE   	(1<<3)	/* Spacer */
#define LEFT    	(1<<4)	/* Left justified */
#define HEX_PREP 	(1<<5)	/* 0x */
#define UPPERCASE   (1<<6)	/* 'ABCDEF' */

#define is_digit(c) ((c) >= '0' && (c) <= '9')

char lower_digits_str[] = "0123456789abcdefghijklmnopqrstuvwxyz";
static char *lower_digits = lower_digits_str;
char upper_digits_str[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char *upper_digits = upper_digits_str;

static int ee_skip_atoi(const char **s)
{
  int i = 0;
  while (is_digit(**s)) {
  	i = i*10 + *((*s)++) - '0';
  }
  return i;
}

static char *ee_number(char *str, long num, int base, int size, int precision, int type)
{
  char c, sign, tmp[66];
  char *dig = lower_digits;
  int i;

  if (type & UPPERCASE) {
  	dig = upper_digits;
  }
  if (type & LEFT) {
  	type &= ~ZEROPAD;
  }
  if (base < 2 || base > 36) {
  	return 0;
  }
  
  c = (type & ZEROPAD) ? '0' : ' ';
  sign = 0;
  if (type & SIGN) {
    if (num < 0) {
      sign = '-';
      num = -num;
      size--;
    } else if (type & PLUS) {
      sign = '+';
      size--;
    } else if (type & SPACE) {
      sign = ' ';
      size--;
    }
  }

  if (type & HEX_PREP) {
  	size -= (base == 16) ? 2: 1;
  }

  i = 0;

  if (num == 0) {
    tmp[i++] = '0';
  } else {
    while (num != 0) {
      tmp[i++] = dig[((unsigned long) num) % (unsigned) base];
      num = ((unsigned long) num) / (unsigned) base;
    }
  }

  if (i > precision) {
  	precision = i;
  }
  size -= precision;
  if (!(type & (ZEROPAD | LEFT))) {
  	while (size-- > 0) {
  		*str++ = ' ';
  	}
  }
  if (sign) {
  	*str++ = sign;
  }
  
  if (type & HEX_PREP) {
    if (base == 8) {
      *str++ = '0';
    } else if (base == 16) {
      *str++ = '0';
      *str++ = lower_digits[33];
    }
  }

  if (!(type & LEFT)) {
  	while (size-- > 0) {
  		*str++ = c;
  	}
  }
  while (i < precision--) {
  	*str++ = '0';
  }
  while (i-- > 0) {
  	*str++ = tmp[i];
  }
  while (size-- > 0) {
  	*str++ = ' ';
  }

  return str;
}

static char *eaddr(char *str, unsigned char *addr, int size, int precision, int type)
{
  char tmp[24];
  char *dig = lower_digits;
  int i, len;

  if (type & UPPERCASE)  dig = upper_digits;
  len = 0;
  for (i = 0; i < 6; i++) {
    if (i != 0) {
    	tmp[len++] = ':';
    }
    tmp[len++] = dig[addr[i] >> 4];
    tmp[len++] = dig[addr[i] & 0x0F];
  }

  if (!(type & LEFT)) {
  	while (len < size--) {
  		*str++ = ' ';
  	}
  }
  for (i = 0; i < len; ++i) {
  	*str++ = tmp[i];
  }
  while (len < size--) {
  	*str++ = ' ';
  }

  return str;
}

static char *iaddr(char *str, unsigned char *addr, int size, int precision, int type)
{
  char tmp[24];
  int i, n, len;

  len = 0;
  for (i = 0; i < 4; i++) {
    if (i != 0) {
    	tmp[len++] = '.';
    }
    n = addr[i];
    
    if (n == 0) {
      tmp[len++] = lower_digits[0];
    } else {
      if (n >= 100)  {
        tmp[len++] = lower_digits[n / 100];
        n = n % 100;
        tmp[len++] = lower_digits[n / 10];
        n = n % 10;
      } else if (n >= 10) {
        tmp[len++] = lower_digits[n / 10];
        n = n % 10;
      }

      tmp[len++] = lower_digits[n];
    }
  }

  if (!(type & LEFT)) {
  	while (len < size--) {
  		*str++ = ' ';
  	}
  }
  for (i = 0; i < len; ++i) {
  	*str++ = tmp[i];
  }
  while (len < size--) {
  	*str++ = ' ';
  }

  return str;
}

int ee_vsprintf(char *buf, const char *fmt, va_list args)
{
  int len;
  unsigned long num;
  int i, base;
  char *str;
  char *s;

  int flags;            // Flags to number()

  int field_width;      // Width of output field
  int precision;        // Min. # of digits for integers; max number of chars for from string
  int qualifier;        // 'h', 'l', or 'L' for integer fields

  for (str = buf; *fmt; fmt++) {
    if (*fmt != '%') {
      *str++ = *fmt;
      continue;
    }
                  
    // Process flags
    flags = 0;
repeat:
    fmt++; // This also skips first '%'
    switch (*fmt) {
      case '-':
      	flags |= LEFT;
      	goto repeat;
      case '+':
      	flags |= PLUS;
      	goto repeat;
      case ' ':
      	flags |= SPACE;
      	goto repeat;
      case '#':
      	flags |= HEX_PREP;
      	goto repeat;
      case '0':
      	flags |= ZEROPAD;
      	goto repeat;
    }
          
    // Get field width
    field_width = -1;
    if (is_digit(*fmt)) {
      field_width = ee_skip_atoi(&fmt);
    } else if (*fmt == '*') {
      fmt++;
      field_width = va_arg(args, int);
      if (field_width < 0) {
        field_width = -field_width;
        flags |= LEFT;
      }
    }

    // Get the precision
    precision = -1;
    if (*fmt == '.') {
      ++fmt;    
      if (is_digit(*fmt)) {
        precision = ee_skip_atoi(&fmt);
      } else if (*fmt == '*') {
        ++fmt;
        precision = va_arg(args, int);
      }
      if (precision < 0) {
      	precision = 0;
      }
    }

    // Get the conversion qualifier
    qualifier = -1;
    if (*fmt == 'l' || *fmt == 'L') {
      qualifier = *fmt;
      fmt++;
    }

    // Default base
    base = 10;

    switch (*fmt) {
      case 'c':
        if (!(flags & LEFT)) {
        	while (--field_width > 0) {
        		*str++ = ' ';
        	}
        }
        *str++ = (unsigned char) va_arg(args, int);
        while (--field_width > 0) {
        	*str++ = ' ';
        }
        continue;

      case 's':
        s = va_arg(args, char *);
        if (!s) {
        	char null_str[] = "<NULL>";
        	s = null_str;
        }
        len = strnlen(s, precision);
        if (!(flags & LEFT)) {
        	while (len < field_width--) {
        		*str++ = ' ';
        	}
        }
        for (i = 0; i < len; ++i) {
        	*str++ = *s++;
        }
        while (len < field_width--) {
        	*str++ = ' ';
        }
        continue;

      case 'p':
        if (field_width == -1) {
          field_width = 2 * sizeof(void *);
          flags |= ZEROPAD;
        }
        str = ee_number(str, (unsigned long) va_arg(args, void *), 16, field_width, precision, flags);
        continue;

      case 'A':
        flags |= UPPERCASE;

      case 'a':
        if (qualifier == 'l') {
          str = eaddr(str, va_arg(args, unsigned char *), field_width, precision, flags);
        } else {
          str = iaddr(str, va_arg(args, unsigned char *), field_width, precision, flags);
        }
        continue;

      // Integer number formats - set up the flags and "break"
      case 'o':
        base = 8;
        break;

      case 'X':
        flags |= UPPERCASE;

      case 'x':
        base = 16;
        break;

      case 'd':
      case 'i':
        flags |= SIGN;

      case 'u':
        break;

      default:
        if (*fmt != '%') {
        	*str++ = '%';
        }
        if (*fmt) {
          *str++ = *fmt;
        } else {
          --fmt;
        }
        continue;
    }

    if (qualifier == 'l') {
      num = va_arg(args, unsigned long);
    } else if (flags & SIGN) {
      num = va_arg(args, int);
    } else {
      num = va_arg(args, unsigned int);
    }

    str = ee_number(str, num, base, field_width, precision, flags);
  }

  *str = '\0';
  return str - buf;
}