#========================================
# Makefile
#========================================
#----------------------------------------
# Tool settings
#----------------------------------------
DEVKIT_BIN_DIR = $(HOME)/bin/kumikomios/devkitPro/devkitARM/bin
GCC            = $(DEVKIT_BIN_DIR)/arm-none-eabi-gcc
LD             = $(DEVKIT_BIN_DIR)/arm-none-eabi-ld
OBJCOPY        = $(DEVKIT_BIN_DIR)/arm-none-eabi-objcopy
VBA            = /Applications/Visual\ Boy\ Advance/VisualBoyAdvance.app/Contents/MacOS/VisualBoyAdvance
OPTUSB         = optusb
CFLAGS         = -W -Wall -Wno-attributes

#----------------------------------------
# File and Directory settings
#----------------------------------------
TARGET = main.mb
TARGET_OUT = $(patsubst %.mb, %.out, $(TARGET))
INCLUDE_DIR = include
SRCS_DIR = src
OBJ_DIR = build
BIN_DIR = bin
GCC_LS = -T $(SRCS_DIR)/gcc.ls
CRT = $(filter-out $(SRCS_DIR), $(shell find $(SRCS_DIR) -name "*.S"))
CRT_OBJ = $(addprefix $(OBJ_DIR)/, $(subst $(SRCS_DIR)/, , $(patsubst %.S, %.o, $(CRT))))
SRCS = $(filter-out $(SRCS_DIR), $(shell find $(SRCS_DIR) -name "*.c"))
OBJS = $(addprefix $(OBJ_DIR)/, $(subst $(SRCS_DIR)/, , $(patsubst %.c, %.o, $(SRCS))))

#----------------------------------------
# Tasks
#----------------------------------------
default:
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	@[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
	@make all

all: $(TARGET)

$(TARGET): $(TARGET_OUT)
	$(OBJCOPY) -O binary $(OBJ_DIR)/$^ $(BIN_DIR)/$@

$(TARGET_OUT): $(CRT_OBJ) $(OBJS)
	$(LD) -o $(OBJ_DIR)/$@ $(GCC_LS) $(CRT_OBJ) $^

$(CRT_OBJ): $(CRT)
	$(GCC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	$(GCC) $(CFLAGS) -I $(INCLUDE_DIR) -o $@ -c $<

run-gba: $(TARGET)
	$(OPTUSB) $(BIN_DIR)/$^

run: $(TARGET)
	$(VBA) $(BIN_DIR)/$^ 1>/dev/null 2>/dev/null &

clean:
	rm -f $(OBJ_DIR)/*
	rm -f $(BIN_DIR)/*

.PHONY: clean
