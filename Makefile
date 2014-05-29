all: main.mb

DEVKIT_BIN_DIR = $(HOME)/bin/kumikomios/devkitPro/devkitARM/bin
GCC            = $(DEVKIT_BIN_DIR)/arm-none-eabi-gcc
LD             = $(DEVKIT_BIN_DIR)/arm-none-eabi-ld
OBJCOPY        = $(DEVKIT_BIN_DIR)/arm-none-eabi-objcopy
VBA            = /Applications/Visual\ Boy\ Advance/VisualBoyAdvance.app/Contents/MacOS/VisualBoyAdvance

crt.o: crt.S
	$(GCC) -c crt.S

main.o: gba.h delay.h ball.h racket.h main.c
	$(GCC) -c main.c

utils.o: gba.h utils.h utils.c
	$(GCC) -c utils.c

game.o: gba.h utils.h game.h game.c
	$(GCC) -c game.c

box.o: gba.h utils.h box.h box.c
	$(GCC) -c box.c

ball.o: gba.h utils.h game.h box.h ball.h ball.c
	$(GCC) -c ball.c

racket.o: gba.h utils.h game.h box.h ball.h racket.h racket.c
	$(GCC) -c racket.c

block.o: gba.h block.h block.c
	$(GCC) -c block.c

main.mb: main.o crt.o utils.o game.o box.o ball.o racket.o block.o
	$(LD) -o main.out -T gcc.ls crt.o utils.o game.o box.o ball.o racket.o block.o main.o
	$(OBJCOPY) -O binary main.out main.mb

clean:
	/bin/rm -f *.o *.bin *.out *.mb

trans: main.mb
	optusb main.mb

run: main.mb
	$(VBA) main.mb 1>/dev/null 2>/dev/null &
