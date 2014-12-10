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

/**
 * Determine how to handle the incoming message.
 * @param byte the byte to look at.
 * @return a positive integer, the total size of the
 *         midi message, if the given byte marks the
 *         start of a midi message.
 * @return zero if the byte is a data-byte of another
 *         midi-message
 * @return -1 for reserved messages
 * @return -2 for sysex messages
 */
int8_t midi_peek( const uint8_t byte ) {
  static const int8_t msg_size_voice[8] = {
    3, 3, 3, 3,
    2, 2, 3, -1
  };
  static const int8_t msg_size_common[16] = {
    -2, 2, 3, 2,
    -1, -1, 1, 1,
    1, -1, 1, 1,
    1, -1, 1, 1
  };
  if (byte < 0x80) {
    return 0;
  } else if (byte < 0xf0) {
    return msg_size_voice[(byte>>4) & 0x07];
  } else {
    return msg_size_common[byte & 0x0f];
  }
}

/**
 * Receive a single byte and store it in the internal buffer.
 * @param in the midi-in port
 * @param byte the byte that was received
 */
void midi_recv( midi_in_t* in, const uint8_t byte ) {
  int8_t len = midi_peek( byte );
  if (len == 0) {
    if (in->sysx) {
      /* handle sysex data */
    } else {
      in->msg.data[in->moff++] = byte;
    }
  } else if (len > 0) {
    if (/* realtime? */ 0) {
      /* handle realtime signals immediately */
    } else {
      in->msg.data[0] = byte;
      in->mlen = len;
      in->moff = 1;
    }
  } else if (len < 0) {
    in->mlen = 0;
    in->moff = 0;
  }
}

void midi_poll( midi_in_t* in ) {
  if (in->mlen == in->moff && in->mlen > 0) {
    /* handle message */
    in->recv( in, in->msg );
    /* prepare for rolling status */
    in->moff = 1;
  }
}
