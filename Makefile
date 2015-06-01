#######################################################################
# 
# Makefile
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#######################################################################

TEXT_BASE  = 0x8000
CROSS_COMPILE = arm-linux-gnueabihf-

AS      = $(CROSS_COMPILE)as
AR	= $(CROSS_COMPILE)ar
LD      = $(CROSS_COMPILE)ld
CC      = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy 

CPPFLAGS = -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -Os -fno-stack-protector -g -fstack-usage -Wno-format-nonliteral -nostartfiles -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -mword-relocations -mno-unaligned-access -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -msoft-float -pipe -march=armv7-a 
CFLAGS   = $(CPPFLAGS) -c
LDFLAGS  = -nostdlib -Bstatic -T ldscript.lds -Ttext $(TEXT_BASE) 
LIBGCC := -L $(shell dirname `$(CC) $(CFLAGS) -print-libgcc-file-name`) -lgcc

OBJS    := $(shell ls *.c)
OBJS    := $(OBJS:.c=.o)
SOBJS   := $(shell ls *.S)
SOBJS   := $(SOBJS:.S=.o)

all:    clean rpi2boot.bin

rpi2boot.bin:rpi2boot
	@$(OBJCOPY) -O binary rpi2boot rpi2boot.bin
	@ls -lh rpi2boot.bin

rpi2boot: $(OBJS) $(SOBJS)
	@$(LD) $(LDFLAGS) $(OBJS) $(SOBJS) $(LIBGCC) -Map rpi2boot.map -o rpi2boot

clean : 
	@rm -f *.o *.su
	@rm -f rpi2boot rpi2boot.bin rpi2boot.map 

%.o:    %.S
	@$(AS) -o $@ $<
%.o:    %.c
	@$(CC) $(CFLAGS) $<
