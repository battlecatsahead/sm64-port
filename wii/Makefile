###
##
# Makefile for app_booter.
##

CROSS   := $(DEVKITPPC)/bin/powerpc-eabi-

OBJCOPY := $(CROSS)objcopy
CC      := $(CROSS)gcc
LD      := $(CROSS)ld

BIN_TARGET := app_booter.bin
ELF_TARGET := app_booter.elf

LIBDIRS :=
INCLUDE := -I.

INCLUDE += -I$(DEVKITPRO)/libogc/include
LIBDIRS += -L$(DEVKITPRO)/libogc/lib/wii

MACHDEP := -DHW_RVL -DGEKKO -mno-eabi -mno-sdata -mcpu=750
# todo: find out why -Os spits out linker errors
CFLAGS += -Wall -O2 -ffreestanding -std=gnu99 $(MACHDEP) $(INCLUDE)

LDFLAGS := -T link.ld

OBJ = crt0.o main.o string.o

all: $(BIN_TARGET)

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

$(ELF_TARGET): $(OBJ)
	$(LD) -o $@ $(LDFLAGS) $(LIBDIRS) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BIN_TARGET)
	rm -f $(ELF_TARGET)
	rm -f $(OBJ)

.PHONY: clean
