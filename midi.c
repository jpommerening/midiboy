#include <avr/io.h>
#include <avr/interrupt.h>
#include "midi.h"

#define F_CPU16 (F_CPU/16)
#define MIDI_BAUD 31250
#define MIDI_UBRR (F_CPU16/MIDI_BAUD) - 1

/* setup uart and interrupts */
void midi_init( midi_t* port ) {
  UBRRH = (unsigned char) ((MIDI_UBRR >> 8) & 0x0f);
  UBRRL = (unsigned char) (MIDI_UBRR & 0xff);

  // asynchronous (UMSEL1..0 = 00)
  // no parity (UPM1..0 = 00)
  // 1 stop bit (USBS = 0)
  // 8 bits (UCSZ1..0 = 11)
  // falling XCK edge (UCPOL = 0)
  UCSRC = (1<<UCSZ0) | (1<<UCSZ1);

  // (maybe) enable receive, transmit + interrupts
  UCSRB = ((port->rxen) << RXEN) | ((port->rxen) << RXCIE)
        | ((port->txen) << TXEN) | ((port->txen) << TXCIE);
}

ISR(USART0_RX_vect) {
}

ISR(USART0_TX_vect) {
}
