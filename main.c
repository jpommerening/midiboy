#include <avr/io.h>
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
  DDRB = 0x1f; // PB0 - PB04 = out

  midi_t mport;

  mport.rxen = 1;
  mport.omni = 1;
  mport.chan = 0;

  uint8_t x = 0;

  midi_init( &mport );

  while (1) {
    _delay_ms( 1000 );
    PORTB = x;
    x = (x+1) & 0x03;
  }

  return 0;
}

