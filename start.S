/*
 * Startup code
 *
 * Copyright (c) 2004   Texas Instruments <r-woodruff2@ti.com>
 *
 * Copyright (c) 2001   Marius Gröger <mag@sysgo.de>
 * Copyright (c) 2002   Alex Züpke <azu@sysgo.de>
 * Copyright (c) 2002   Gary Jennejohn <garyj@denx.de>
 * Copyright (c) 2003   Richard Woodruff <r-woodruff2@ti.com>
 * Copyright (c) 2003   Kshitij <kshitij@ti.com>
 * Copyright (c) 2006-2008 Syed Mohammed Khasim <x0khasim@ti.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

.global _reset
.global main
.global _start
.global pl011_serial_init

_reset:
        /*
	 * disable interrupts (FIQ and IRQ), also set the cpu to SVC32 mode,
	 * except if in HYP mode already
	 */
	mrs	r0, cpsr
	and	r1, r0, #0x1f		@ mask mode bits
	teq	r1, #0x1a		@ test for HYP mode
	bicne	r0, r0, #0x1f		@ clear all mode bits
	orrne	r0, r0, #0x13		@ set SVC mode
	orr	r0, r0, #0xc0		@ disable FIQ and IRQ
	msr	cpsr,r0

	/* Set V=0 in CP15 SCTLR register - for VBAR to point to vector */
	mrc     p15, 0, r0, c1, c0, 0	@ Read CP15 SCTLR Register
	bic     r0, #0x2000		@ V = 0
	mcr     p15, 0, r0, c1, c0, 0	@ Write CP15 SCTLR Register

	/* Set vector address in CP15 VBAR register */
	ldr     r0, =_start
	mcr     p15, 0, r0, c12, c0, 0	@Set VBAR

	/* Set up stack pointer */
	ldr     sp, =0x7FFF000	@ 4K size
        bic     sp, sp, #7      @ 8-byte alignment for ABI compliance

	bl	pl011_serial_init	@ Initialize serial port
	bl	main			@ Call main function
