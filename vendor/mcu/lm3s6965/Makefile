
STELLARISWARE=/home/liuziloong/StellarisWare

CC=arm-none-eabi-gcc -Wall -Os -march=armv7-m -mcpu=cortex-m3 -mthumb -mfix-cortex-m3-ldrd -Wl,--gc-sections

lx.bin: lx.elf
	arm-none-eabi-objcopy -O binary rhino.elf lx.bin

rhino.elf: rhino.c startup.c
	${CC} -o $@ -I${STELLARISWARE} -L${STELLARISWARE}/driverlib/gcc-cm3  -I/home/liuziloong/StellarisWare/boards/ek-lm3s6965 -Tlink.lds  lx.c startup.c -ldriver-cm3

.PHONY: clean
clean:
	rm -f *.elf *.bin

