/*
 * API declarations
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __EXPORTS_H
#define __EXPORTS_H

#include "type_defs.h"

/* stdin */
int getc(void);
int tstc(void);

/* stdout */
void putc(const char c);
void puts(const char *s);
void printf(const char *fmt, ...);
int sprintf(char * buf, const char *fmt, ...);

/* Serial APIs */
void serial_putc(char ch);
int serial_getc(void);
int serial_tstc(void);
void pl011_serial_init(void);

/* Timer APIs */
u32 get_timer_ticks(void);
void udelay(u32 usec);
void mdelay(u32 msec);
void delay(u32 sec);

#endif
