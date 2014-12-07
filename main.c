#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifdef DEBUG
#include "simulavr_info.h"
#define STR(x) #x
SIMINFO_DEVICE(STR(MCU));
SIMINFO_CPUFREQUENCY(F_CPU);
SIMINFO_SERIAL_IN("B3",STR(DATA),BAUD);
#undef STR
#endif

#include "midi.h"

int main( void ) {
  DDRB = 0x0f;
  PORTB = 0x30;

  midi_t mport;

  mport.rxen = 1;
  mport.omni = 1;
  mport.chan = 0;

  //midi_init( &mport );
  uint8_t x = 0;

  while (1) {
    x = (PINB & 0x30) >> 4;
    PORTB = x | 0x30;
  }

  return 0;
}
