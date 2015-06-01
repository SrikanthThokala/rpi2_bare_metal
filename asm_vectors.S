/*
 * Exception Vector table
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

.org 0
.text

.globl _reset
.globl _start

.globl fiq_handler
.globl irq_handler
.globl swi_handler
.globl data_abort_handler
.globl prefetch_abort_handler

.globl irq_handler

.section .vectors
_start:
	b       _reset
	b	undefined_instr_intr
	b	swi_intr
	b	prefetch_abort_intr
	b	data_abort_intr
	nop
	b	irq_intr
	b	fiq_intr

irq_intr:
        stmdb	sp!,{r0-r3,r12,lr}
        bl	irq_handler
        ldmia	sp!,{r0-r3,r12,lr}
        sub	pc, lr, #4

fiq_intr:
        stmdb	sp!,{r0-r3,r12,lr}
        bl	fiq_handler
        ldmia	sp!,{r0-r3,r12,lr}
        subs	pc, lr, #4

undefined_instr_intr:
        stmdb	sp!,{r0-r3,r12,lr}
        ldmia	sp!,{r0-r3,r12,lr}
        b	_reset
        movs	pc, lr

swi_intr:
	stmdb	sp!,{r0-r3,r12,lr}
	tst	r0, #0x20
	ldrneh	r0, [lr,#-2]
	bicne	r0, r0, #0xff00
	ldreq	r0, [lr,#-4]
	biceq	r0, r0, #0xff000000
	bl	swi_handler
	ldmia	sp!,{r0-r3,r12,lr}
	subs	pc, lr, #4

data_abort_intr:
	stmdb	sp!,{r0-r3,r12,lr}
	bl	data_abort_handler
	ldmia	sp!,{r0-r3,r12,lr}
	subs	pc, lr, #4

prefetch_abort_intr:
	stmdb	sp!,{r0-r3,r12,lr}
	bl	prefetch_abort_handler
	ldmia	sp!,{r0-r3,r12,lr}
	subs	pc, lr, #4
