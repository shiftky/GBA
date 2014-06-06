DEVKIT_BIN_DIR = $(HOME)/bin/kumikomios/devkitPro/devkitARM/bin
GCC            = $(DEVKIT_BIN_DIR)/arm-none-eabi-gcc
LD             = $(DEVKIT_BIN_DIR)/arm-none-eabi-ld
OBJCOPY        = $(DEVKIT_BIN_DIR)/arm-none-eabi-objcopy
VBA            = /Applications/Visual\ Boy\ Advance/VisualBoyAdvance.app/Contents/MacOS/VisualBoyAdvance
CFLAGS         = -W -Wall -Wno-attributes

TARGET = main.mb
SRCS_DIR = src
INCR_DIR = include
OBJDIR = build

SRCS = $(filter-out $(SRCS_DIR), $(shell find $(SRCS_DIR) -name "*.c") $(shell find $(SRCS_DIR) -name "*.S"))
OBJS = $(addprefix $(OBJDIR)/, $(subst $(SRCS_DIR)/, "", $(patsubst %.c, %.o, $(SRCS))))

test:
	@echo $(SRCS)
	@echo $(OBJS)
