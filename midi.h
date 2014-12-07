typedef struct {
  unsigned rxen : 1;
  unsigned txen : 1;
  unsigned omni : 1;
  unsigned pad_ : 1;
  unsigned chan : 4;
} midi_t;

void midi_init( midi_t* port );
