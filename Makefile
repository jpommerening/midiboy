
MCU = attiny2313
F_CPU = 8000000
BAUD = 31250
DATA = mididata

MKDIR_P = mkdir -p
CC = avr-gcc
CPPFLAGS = -DMCU=$(MCU)a -DF_CPU=$(F_CPU)UL -DBAUD=$(BAUD) -DDATA=$(DATA) -Wall -Wextra
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

test:
	simavr -m $(MCU) -f $(F_CPU) $(BIN)

