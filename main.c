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

#include "midi.h"

typedef struct state_s {
  uint8_t frame;
} state_t;

static midi_in_t in = MIDI_IN_INIT;

static void recv( midi_in_t* in, const midi_msg_t msg ) {
  state_t* state = in->info;
  if (MIDI_STATUS(msg) == CLOCK) {
    state->frame = (state->frame + 1) % 24;
  }
}

ISR (USART0_RX_vect) {
  midi_recv(&in, UDR);
}

ISR (USART0_TX_vect) {
}

/*
 * Clock uses the 16bit timer in CTC (clear timer on compare match) mode.
 * TCNT1H and TCNT1L are the 16bit value of the timer
 * OCR1AH and OCR1AL define the "modulus" for the timer and thus
 * the interrupt interval.
 * OCIE1A enables the interrupt fired, when OSC1A is exceeded.
 * Since all of these happen way to fast for 24ppm at a reasonable bpm,
 * an internal counter is "filled" to trigger the actual clock events.
 */
ISR (TIMER1_COMPA_vect) {
}
ISR (TIMER1_OVF_vect) {
}

void setup( void ) {
  state_t state = {
    0
  };

  in.recv_rt = &recv;
  in.info = &state;

  DDRB = 0x0f;
  PORTB = 0x30;

  UBRRH = (uint8_t) ((MIDI_UBRR >> 8) & 0x0f);
  UBRRL = (uint8_t) (MIDI_UBRR & 0xff);
  UCSRC = (1<<UCSZ0) | (1<<UCSZ1);
  UCSRB = (1<<RXEN) | (1<<RXCIE);
}

void loop( void ) {
  uint8_t x = 0;
  uint16_t blink = 0;
  state_t* state = in.info;

  x = (PINB & 0x30) >> 4;
  midi_poll(&in);
  if (blink) {
    PORTB = 0x30;
    blink--;
  } else {
    PORTB = ((x & 0x01) ? LED1YELLOW : LED1RED)
          | ((x & 0x02) ? LED2GREEN  : LED2RED)
          | 0x30;
  }
  if (state->frame == 0) {
    blink = 15000;
  }
}

int main( void ) {
  cli();
  setup();
  sei();
  while (1) loop();
  return 0;
}
