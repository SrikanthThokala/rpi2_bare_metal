/*
 * ARM Exception Handlers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "exports.h"

/* IRQ Handler */
void irq_handler(void)
{
	printf("IRQ HANDLER\n");
}

/* FIQ Handler */
void fiq_handler(void)
{
	printf("FIQ HANDLER\n");
}

/* SWI Handler */
void swi_handler(void)
{
	printf("SWI HANDLER\n");
}

/* Data Abort Handler */
void data_abort_handler(void)
{
	printf("DATA ABORT HANDLER\n");
}

/* Prefetch Abort Handler */
void prefetch_abort_handler(void)
{
	printf("PREFETCH ABORT HANDLER\n");
}
