all: main.mb

DEVKIT_BIN_DIR = $(HOME)/bin/kumikomios/devkitPro/devkitARM/bin
GCC            = $(DEVKIT_BIN_DIR)/arm-none-eabi-gcc
LD             = $(DEVKIT_BIN_DIR)/arm-none-eabi-ld
OBJCOPY        = $(DEVKIT_BIN_DIR)/arm-none-eabi-objcopy
VBA            = /Applications/Visual\ Boy\ Advance/VisualBoyAdvance.app/Contents/MacOS/VisualBoyAdvance
CFLAGS				= -W -Wall -Wno-attributes

crt.o: crt.S
	$(GCC) $(CFLAGS) -c crt.S

main.o: gba.h utils.h ball.h racket.h main.c
	$(GCC) $(CFLAGS) -c main.c

utils.o: gba.h utils.h utils.c
	$(GCC) $(CFLAGS) -c utils.c

game.o: gba.h utils.h ball.h game.h game.c
	$(GCC) $(CFLAGS) -c game.c

box.o: gba.h utils.h box.h box.c
	$(GCC) $(CFLAGS) -c box.c

ball.o: gba.h utils.h game.h box.h ball.h ball.c
	$(GCC) $(CFLAGS) -c ball.c

racket.o: gba.h utils.h game.h box.h ball.h racket.h racket.c
	$(GCC) $(CFLAGS) -c racket.c

block.o: gba.h block.h block.c
	$(GCC) $(CFLAGS) -c block.c

main.mb: main.o crt.o utils.o game.o box.o ball.o racket.o block.o
	$(LD) -o main.out -T gcc.ls crt.o utils.o game.o box.o ball.o racket.o block.o main.o
	$(OBJCOPY) -O binary main.out main.mb

clean:
	/bin/rm -f *.o *.bin *.out *.mb

trans: main.mb
	optusb main.mb

run: main.mb
	$(VBA) main.mb 1>/dev/null 2>/dev/null &
