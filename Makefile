
MCU = attiny2313a
F_CPU = 10000000UL
BAUD = 31250
DATA = mididata

MKDIR_P = mkdir -p
CC = avr-gcc
CPPFLAGS = -DMCU=$(MCU) -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -DDATA=$(DATA) -Wall -Wextra
CFLAGS = -g -DDEBUG -mmcu=$(MCU) -O2 -Wl,--section-start=.siminfo=0x900000

OBJS = main.o midi.o clock.o
DEPS = $(OBJS:%.o=%.d)
BIN = midiboy.elf

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

-include $(DEPS)

%.d: %.c Makefile
	$(CC) -MM -o $@ $<

%.o: %.c %.d
	$(CC) -Os -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

.PHONY: default all clean

default: all

all: $(BIN)

clean:
	rm -f $(DEPS) $(OBJS) $(BIN)

