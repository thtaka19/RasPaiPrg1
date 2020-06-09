#************************************************************************/
#*      GCC/LLCM ARM Baremetal Software / (C) Toshio MURAI  2012-2016   */
#*      This is Free Software.   You can redistribute this software     */
#*      and/or modify it ,under the terms of the GNU General Public     */
#*      License version 3, or (at your option) any later version.       */
#*      or under the terms of the BSD 3-Clause License.	(Dual Licence)  */
#*        Pai2 Compile  For Pai3  32 Bit      2017 May TT               */
#*                                                                       */
#************************************************************************/
#CPU=cortex-a7
#	ARCH=armv7-a

###  apt-get 
CPATH= /usr/bin/arm-none-eabi-

CC=$(CPATH)gcc
AS=$(CPATH)as
LD=$(CPATH)ld
OBJCOPY=$(CPATH)objcopy

### Try  MEMORYMAP= rpiMicon1.lds main10Arm1x.c  OK !!!!


 OBJECTS= startup01.o startupadd.o  serial.o  gpio.o syscalls.o 
 OBJECTS += led10.o mini_serialPi1.o buzzer.o buttonPi1.o i2c1.o spi0.o 
 OBJECTS += raspGPIO1.o
 OBJECTS += main000.o 
###

#  MEMORYMAP= rpiMicon10.lds
    MEMORYMAP= viperlite10.ld

OBJECTNAME=Rpi00_0Pai1_v001


###  apt-get 
	LIBGCC  = /usr/lib/gcc/arm-none-eabi/4.8.2/
	LIBC = /usr/lib/arm-none-eabi/newlib/



#####   Original ###
#	CFLAGS = -mcpu=$(CPU) -msoft-float -g -O2
	CFLAGS = -msoft-float -g -O2
	CFLAGS+= -I. -I.. -I/usr/local/include
#	ASFLAGS= -mcpu=$(CPU) --defsym HYPER=1 --defsym JTAG=1 # -mfpu=neon
	ASFLAGS= -mcpu=$(CPU) --defsym JTAG=1 # -mfpu=neon

####   RPI 08_0 C Flag
#	CFLAGS = -mfloat-abi=soft -mlittle-endian
#	CFLAGS+= -nostartfiles
#	CFLAGS+= -ffreestanding
#	CFLAGS+= -O0 -g3

#	CFLAGS= -mcpu=$(CPU) -mtune=$(CPU) -march=$(ARCH)	gcc
#	CFLAGS= -target arm-eabi -mcpu=$(CPU) -mtune=$(CPU)	clang

$(OBJECTNAME).out:  $(OBJECTS)
	$(LD) -T $(MEMORYMAP) -Map $(OBJECTNAME).map $(OBJECTS) -L$(LIBGCC) -L$(LIBC) -lc -lgcc -lc -o $(OBJECTNAME).out
	$(OBJCOPY) -O srec $(OBJECTNAME).out $(OBJECTNAME).mot
	$(OBJCOPY) -O ihex $(OBJECTNAME).out $(OBJECTNAME).hex
	$(OBJCOPY) -O binary $(OBJECTNAME).out $(OBJECTNAME).bin
	$(OBJCOPY) -O binary $(OBJECTNAME).out kernel7.img


.S.o:
	$(CC) $(CFLAGS) -c $< -o $@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@




clean	:
	rm -rf *.o $(OBJECTNAME).* kernel*.img *.mot *.hex *.bin *.img *.out
