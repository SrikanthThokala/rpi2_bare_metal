# RPI2 Bare Metal Source

This repository contains bare metal source that will boot up RPI2.  Briefly,
it does following:

* Initialize CPU
* Setup exception vector table
* Initialize Serial and Timer peripherals
* More peripherals to add..

This bare metal source finds application in porting Real Time Operating System
(RTOS) like FreeRTOS, VxWorks and many other embedded applications.

# How to compile?

Linux> make

This generates 'rpi2boot.bin' image which is ready to flash.

# How to run?

* First install any operating system image by following steps in this [link](http://www.raspberrypi.org/documentation/installation/installing-images/README.md)
* After installing image into SD card, cross-check once if it boots as expected.
* Now remove SD card from target and connect it to PC. Mount the SD card.
* Copy the generated image 'rpi2boot.bin' to directory '$(MOUNT_POINT)/boot/'
  as 'kernel7.img'
* Do a 'sync' and remove the card.
* Connect the SD card into target slot and power up.

NOTE: I have tried with installing Raspbian image and others should work too.
Please let me know if it doesn't work as expected.

# References

* [BCM283x Architecture](https://github.com/raspberrypi/documentation/blob/master/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf)
* [Raspberry Pi GIT Repo](https://github.com/raspberrypi)
* [Cortex-A7 MPcore Processor Reference Manual](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0464f/index.html)
