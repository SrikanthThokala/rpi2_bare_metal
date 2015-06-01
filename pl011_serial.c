/*
 * PL011 Serial driver
 *
 * (C) Copyright 2000
 * Rob Taylor, Flying Pig Systems. robt@flyingpig.com.
 *
 * (C) Copyright 2004
 * ARM Ltd.
 * Philippe Robin, <philippe.robin@arm.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "arch_defs.h"
#include "error_defs.h"

/*
 * PL011 Register Definitions
 */
#define PL011_SERIAL_BASE		0x3f201000

#define PL011_SERIAL_DATA_REG		(PL011_SERIAL_BASE + 0x00)
#define PL011_SERIAL_ERR_CLEAR_REG	(PL011_SERIAL_BASE + 0x04)
#define PL011_SERIAL_FLAG_REG		(PL011_SERIAL_BASE + 0x18)
#define PL011_SERIAL_IRDA_PWR_REG	(PL011_SERIAL_BASE + 0x20)
#define PL011_SERIAL_INT_BAUD_REG	(PL011_SERIAL_BASE + 0x24)
#define PL011_SERIAL_FRAC_BAUD_REG	(PL011_SERIAL_BASE + 0x28)
#define PL011_SERIAL_LINE_CTRL_REG	(PL011_SERIAL_BASE + 0x2C)
#define PL011_SERIAL_CTRL_REG		(PL011_SERIAL_BASE + 0x30)

#define PL011_UART_FLAG_REG_TXFF	(1 << 5)
#define PL011_UART_FLAG_REG_RXFE	(1 << 4)

#define PL011_UART_CTRL_REG_RTS		(1 << 11)
#define PL011_UART_CTRL_REG_RXE		(1 << 9)
#define PL011_UART_CTRL_REG_TXE		(1 << 8)
#define PL011_UART_CTRL_REG_UARTEN	(1 << 0)

#define PL011_UART_LINE_CTRL_WLEN_8	(3 << 5)
#define PL011_UART_LINE_CTRL_FEN	(1 << 4)

#define PL011_SERIAL_CLOCK		3000000
#define PL011_SERIAL_BAUD_RATE		115200

/*
 * Driver APIs
 */

static int pl011_tstc(void)
{
	return !(readl(PL011_SERIAL_FLAG_REG) & PL011_UART_FLAG_REG_RXFE);
}

static int set_line_control(void)
{
	u32 lcr;
	/*
	 * Internal update of baud rate register require line
	 * control register write
	 */
	lcr = PL011_UART_LINE_CTRL_WLEN_8 | PL011_UART_LINE_CTRL_FEN;
	writel(lcr, PL011_SERIAL_LINE_CTRL_REG);

	return 0;
}

static void pl011_serial_setbrg(int clock, int baudrate)
{
	u32 temp, divider, remainder, fraction;

	/*
	* Set baud rate
	*
	* IBRD = UART_CLK / (16 * BAUD_RATE)
	* FBRD = RND((64 * MOD(UART_CLK,(16 * BAUD_RATE)))
	*		/ (16 * BAUD_RATE))
	*/
	temp = 16 * baudrate;
	divider = clock / temp;
	remainder = clock % temp;
	temp = (8 * remainder) / baudrate;
	fraction = (temp >> 1) + (temp & 1);

	writel(divider, PL011_SERIAL_INT_BAUD_REG);
	writel(fraction, PL011_SERIAL_FRAC_BAUD_REG);

	set_line_control();

	/* Finally, enable the UART */
	writel(PL011_UART_CTRL_REG_UARTEN | PL011_UART_CTRL_REG_TXE |
		PL011_UART_CTRL_REG_RXE | PL011_UART_CTRL_REG_RTS,
		PL011_SERIAL_CTRL_REG);
}

static int pl011_putc(char c)
{
	/* Wait until there is space in the FIFO */
	if (readl(PL011_SERIAL_FLAG_REG) & PL011_UART_FLAG_REG_TXFF)
		return -EAGAIN;

	/* Send the character */
	writel(c, PL011_SERIAL_DATA_REG);

	return 0;
}

static int pl011_getc(void)
{
	u32 data;

	/* Wait until there is data in the FIFO */
	if (readl(PL011_SERIAL_FLAG_REG) & PL011_UART_FLAG_REG_RXFE)
		return -EAGAIN;

	data = readl(PL011_SERIAL_DATA_REG);

	/* Check for an error flag */
	if (data & 0xFFFFFF00) {
		/* Clear the error */
		writel(0xFFFFFFFF, PL011_SERIAL_ERR_CLEAR_REG);
		return -1;
	}

	return (int) data;
}

void serial_putc(char ch)
{
	int err;

	do {
		err = pl011_putc(ch);
	} while (err == -EAGAIN);

	if (ch == '\n')
		serial_putc('\r');
}

int serial_getc(void)
{
	int err;

	do {
		err = pl011_getc();
	} while (err == -EAGAIN);

	return err >= 0 ? err : 0;
}

int serial_tstc(void)
{
	return pl011_tstc();
}

void pl011_serial_init(void)
{
	/* disable everything */
	writel(0, PL011_SERIAL_CTRL_REG);

	/* Set Baud Rate */
	pl011_serial_setbrg(PL011_SERIAL_CLOCK, PL011_SERIAL_BAUD_RATE);
}
