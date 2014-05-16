all: main.bin

DEVKIT_BIN_DIR=$(HOME)/bin/kumikomios/devkitPro/devkitARM/bin
GCC=$(DEVKIT_BIN_DIR)/arm-none-eabi-gcc
LD=$(DEVKIT_BIN_DIR)/arm-none-eabi-ld
OBJCOPY=$(DEVKIT_BIN_DIR)/arm-none-eabi-objcopy

crt.o: crt.S
	$(GCC) -c crt.S

main.o: main.c
	$(GCC) -c main.c

box.o: gba.h box.h box.c
	$(GCC) -c box.c

ball.o: gba.h box.h ball.h ball.c
	$(GCC) -c ball.c

racket.o: gba.h box.h ball.h racket.h racket.c
	$(GCC) -c racket.c

main.bin: main.o crt.o box.o ball.o racket.o
	$(LD) -o main.out -T gcc.ls crt.o box.o ball.o racket.o main.o
	$(OBJCOPY) -O binary main.out main.bin

clean:
	/bin/rm -f *.o *.bin *.out
