#include <stddef.h>
#include <stdint.h>

#define MIDI_MSG_INIT { 0 }
#define MIDI_MSG_INIT_STATUS(status) { .data = { status, 0, 0, 0 } }
#define MIDI_IN_INIT { 0, 1, 0, 0, 0, 0, MIDI_MSG_INIT, NULL, NULL }
#define MIDI_OUT_INIT {}

#define _MIDI_MSG_BYTE(msg,n) ((uint8_t*) (&msg))[n]
#define _MIDI_STATUS(byte) ((byte < 0xf0) ? (byte & 0xf0) : byte)
#define _MIDI_CHANNEL(byte) ((byte < 0xf0) ? (byte & 0x0f) : -1)
#define MIDI_STATUS(msg) _MIDI_STATUS(_MIDI_MSG_BYTE(msg,0))
#define MIDI_CHANNEL(msg) _MIDI_CHANNEL(_MIDI_MSG_BYTE(msg,0))

typedef enum {
  NOTE_OFF = 0x80,
  NOTE_ON = 0x90,
  KEY_PRESSURE = 0xa0,
  CONTROL_CHANGE = 0xb0,
  PROGRAM_CHANGE = 0xc0,
  CHANNEL_PRESSURE = 0xd0,
  PITCH_BEND = 0xe0,

  SYSEX_START = 0xf0,
  MTC_QUARTER_FRAME = 0xf1,
  SONG_POSITION = 0xf2,
  SONG_SELECT = 0xf3,
  TUNE_REQUEST = 0xf6,
  SYSEX_END = 0xf7,

  CLOCK = 0xf8,
  START = 0xfa,
  CONTINUE = 0xfb,
  STOP = 0xfc,

  KEEPALIVE = 0xfe,
  RESET = 0xff
} midi_status_t;

typedef struct midi_in_s midi_in_t;

typedef union {
  uint32_t msg;
  uint8_t  data[4];
  struct {
    unsigned type : 4;
    unsigned chan : 4;
    uint8_t  data[3];
  } voice;
  struct packed {
    uint8_t type;
    uint8_t data[3];
  } common;
} midi_msg_t;

typedef void (*midi_recv_cb)( midi_in_t*, const midi_msg_t );
typedef void (*midi_send_cb)( midi_in_t* );

struct midi_in_s {
  unsigned chan : 4;
  unsigned omni : 1;
  unsigned sysx : 1;
  unsigned _pad : 2;

  unsigned mlen : 4;
  unsigned moff : 4;
  midi_msg_t msg;

  midi_recv_cb recv;
  midi_recv_cb recv_rt;
};
