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

#define LED1RED 0x01
#define LED2RED 0x02
#define LED1YELLOW 0x04
#define LED2GREEN 0x08

#define F_CPU16 (F_CPU/16)
#define MIDI_BAUD 31250
#define MIDI_UBRR ((F_CPU16/MIDI_BAUD) - 1)

static uint8_t frame = 0;
static uint8_t msg = 0;

int main( void ) {
  DDRB = 0x0f;
  PORTB = 0x30;

  uint8_t x = 0;
  uint16_t blink = 0;

  PORTB = LED1RED | LED2RED | 0x30;

  UBRRH = (uint8_t) ((MIDI_UBRR >> 8) & 0x0f);
  UBRRL = (uint8_t) (MIDI_UBRR & 0xff);
  UCSRC = (1<<UCSZ0) | (1<<UCSZ1);
  UCSRB = (1<<RXEN) | (1<<RXCIE);

  sei();

  while (1) {
    x = (PINB & 0x30) >> 4;
    if (blink) {
      PORTB = 0x30;
      blink--;
    } else {
      PORTB = ((x & 0x01) ? LED1YELLOW : LED1RED)
            | ((x & 0x02) ? LED2GREEN  : LED2RED)
            | 0x30;
    }
    if (frame == 0) {
      blink = 15000;
      msg = 0;
    }
  }

  return 0;
}

ISR(USART0_RX_vect) {
  msg = UDR;
  frame = (++frame) % 24;
}

ISR(USART0_TX_vect) {
}
