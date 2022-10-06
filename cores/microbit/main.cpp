#include "Arduino.h"

MicroBit uBit;

int main(void) {
  uBit.init();

  setup();

  for (;;) {
    loop();
  }

  return 0;
}
