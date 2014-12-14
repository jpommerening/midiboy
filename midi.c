#include "midi.h"

#define REALTIME 0xf0
#define UNDEFINED 0xf1

/**
 * Determine how to handle the incoming message.
 * @param byte the byte to look at.
 * @return a positive integer, the total size of the
 *         midi message, if the given byte marks the
 *         start of a midi message.
 * @return zero if the byte is a data-byte of another
 *         midi-message
 * @return REALTIME for realtime messages
 * @return UNDEFINED for reserved messages
 * @return SYSEX_START for sysex start messages
 * @return SYSEX_END for sysex end messages
 */
int8_t midi_peek( const uint8_t byte ) {
  static const int8_t msg_info_voice[7] = {
    3, 3, 3, 3,
    2, 2, 3
  };
  static const int8_t msg_info_common[16] = {
    SYSEX_START, 2, 3, 2,
    UNDEFINED, UNDEFINED, 1, SYSEX_END,
    REALTIME, UNDEFINED, REALTIME, REALTIME,
    REALTIME, UNDEFINED, REALTIME, REALTIME
  };
  if (byte < 0x80) {
    return 0;
  } else if (byte < 0xf0) {
    return msg_info_voice[(byte>>4) & 0x07];
  } else {
    return msg_info_common[byte & 0x0f];
  }
}

static void _midi_recv( midi_in_t* in, const midi_msg_t msg ) {
  if (in->recv != NULL) {
    in->recv(in, msg);
  }
}

static void _midi_recv_rt( midi_in_t* in, const uint8_t byte ) {
  midi_msg_t msg = MIDI_MSG_INIT_STATUS(byte);
  if (in->recv_rt != NULL) {
    in->recv_rt(in, msg);
  } else {
    _midi_recv(in, msg);
  }
}

/**
 * Receive a single byte and store it in the internal buffer.
 * @param in the midi-in port
 * @param byte the byte that was received
 */
void midi_recv( midi_in_t* in, const uint8_t byte ) {
  int8_t info = midi_peek(byte);
  if (info == (int8_t)REALTIME) {
    _midi_recv_rt(in, byte);
  } else if (info == 0) {
    if (in->sysx) {
      /* handle sysex data */
    } else {
      in->msg.data[in->moff++] = byte;
      if (in->moff >= sizeof(in->msg)) {
        in->moff = 0;
      }
    }
  } else if (info > 0) {
    in->msg.data[0] = byte;
    in->mlen = info;
    in->moff = 1;
  } else if (info == (int8_t)SYSEX_START) {
    in->sysx = 1;
  } else if (info == (int8_t)SYSEX_END) {
    in->sysx = 0;
  } else if (info == (int8_t)UNDEFINED) {
    in->mlen = 0;
    in->moff = 0;
  } else {
    /* this should never happen */
  }
}

void midi_poll( midi_in_t* in ) {
  if (in->mlen == in->moff && in->mlen > 0) {
    /* handle message */
    _midi_recv(in, in->msg);
    /* prepare for rolling status */
    in->moff = 1;
  }
}
