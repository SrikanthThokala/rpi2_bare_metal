/*
 * System Timer APIs
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "arch_defs.h"

#define SYS_TMR_REG_BASE	0x3f003000

#define SYS_TMR_CTRL_STS	(SYS_TMR_REG_BASE + 0x00)
#define SYS_TMR_CNT_LOW_32	(SYS_TMR_REG_BASE + 0x04)
#define SYS_TMR_CNT_HIGH_32	(SYS_TMR_REG_BASE + 0x08)
#define SYS_TMR_CMP_CHNL_0	(SYS_TMR_REG_BASE + 0x0C)
#define SYS_TMR_CMP_CHNL_1	(SYS_TMR_REG_BASE + 0x10)
#define SYS_TMR_CMP_CHNL_2	(SYS_TMR_REG_BASE + 0x14)
#define SYS_TMR_CMP_CHNL_3	(SYS_TMR_REG_BASE + 0x18)

u32 get_timer_ticks(void)
{
	return readl(SYS_TMR_CNT_LOW_32);
}

void udelay(u32 usec)
{
	u32 end_t;
	int diff_t;

	end_t = get_timer_ticks() + usec;

	do {
		diff_t = end_t - get_timer_ticks();
	} while (diff_t >= 0);
}

void mdelay(u32 msec)
{
	udelay(msec * 1000);
}

void delay(u32 sec)
{
	mdelay(sec * 1000);
}
