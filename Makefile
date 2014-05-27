all: main.mb

DEVKIT_BIN_DIR = $(HOME)/bin/kumikomios/devkitPro/devkitARM/bin
GCC            = $(DEVKIT_BIN_DIR)/arm-none-eabi-gcc
LD             = $(DEVKIT_BIN_DIR)/arm-none-eabi-ld
OBJCOPY        = $(DEVKIT_BIN_DIR)/arm-none-eabi-objcopy
VBA            = /Applications/Visual\ Boy\ Advance/VisualBoyAdvance.app/Contents/MacOS/VisualBoyAdvance

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

main.mb: main.o crt.o box.o ball.o racket.o
	$(LD) -o main.out -T gcc.ls crt.o box.o ball.o racket.o main.o
	$(OBJCOPY) -O binary main.out main.mb

clean:
	/bin/rm -f *.o *.bin *.out *.mb

trans: main.mb
	optusb main.mb

run: main.mb
	$(VBA) main.mb 1>/dev/null 2>/dev/null &
