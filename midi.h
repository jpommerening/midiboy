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

  void (*recv)( midi_in_t* in, const midi_msg_t msg );
};
