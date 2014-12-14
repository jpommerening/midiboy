#ifndef __CLOCK_H
#define __CLOCK_H
#if defined(__cplusplus)
extern "C" {
#endif

#include <stdint.h>

typedef struct clock_s clock_t;
typedef void (*clock_cb)( clock_t*, uint8_t );
struct clock_s {
  unsigned sub : 6;
  unsigned bpm : 10;
  clock_cb clck;
  void* info;
};

void clock_tick( clock_t* clock );
void clock_tap( clock_t* clock );

#if defined(__cplusplus)
}
#endif
#endif
