#include "Arduino.h"

// The micro:bit HAL global instance
MicroBit uBit;

int main(void) {
    uBit.init();

    setup();

    for (;;) {
        loop();
    }

    return 0;
}
