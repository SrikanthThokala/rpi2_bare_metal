/*
 * Architecture specific definitions
 *
 * Copyright (C) 1996-2000 Russell King
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __ARCH_DEFS_H
#define __ARCH_DEFS_H

#include "type_defs.h"

#define __arch_getb(a)		(*(volatile u8 *)(a))
#define __arch_getw(a)		(*(volatile u16 *)(a))
#define __arch_getl(a)		(*(volatile u32 *)(a))
#define __arch_getq(a)		(*(volatile u64 *)(a))

#define __arch_putb(v, a)	(*(volatile u8 *)(a) = (v))
#define __arch_putw(v, a)	(*(volatile u16 *)(a) = (v))
#define __arch_putl(v, a)	(*(volatile u32 *)(a) = (v))
#define __arch_putq(v, a)	(*(volatile u64 *)(a) = (v))


#define __raw_writeb(v, a)	__arch_putb(v, a)
#define __raw_writew(v, a)	__arch_putw(v, a)
#define __raw_writel(v, a)	__arch_putl(v, a)
#define __raw_writeq(v, a)	__arch_putq(v, a)

#define __raw_readb(a)		__arch_getb(a)
#define __raw_readw(a)		__arch_getw(a)
#define __raw_readl(a)		__arch_getl(a)
#define __raw_readq(a)		__arch_getq(a)

#define mb()		asm volatile("dsb sy" : : : "memory")
#define dmb()		__asm__ __volatile__ ("" : : : "memory")
#define __iormb()	dmb()
#define __iowmb()	dmb()

#define writeb(v, c)	({ u8  __v = v; __iowmb(); __arch_putb(__v, c); __v; })
#define writew(v, c)	({ u16 __v = v; __iowmb(); __arch_putw(__v, c); __v; })
#define writel(v, c)	({ u32 __v = v; __iowmb(); __arch_putl(__v, c); __v; })
#define writeq(v, c)	({ u64 __v = v; __iowmb(); __arch_putq(__v, c); __v; })

#define readb(c)	({ u8  __v = __arch_getb(c); __iormb(); __v; })
#define readw(c)	({ u16 __v = __arch_getw(c); __iormb(); __v; })
#define readl(c)	({ u32 __v = __arch_getl(c); __iormb(); __v; })
#define readq(c)	({ u64 __v = __arch_getq(c); __iormb(); __v; })

#endif
