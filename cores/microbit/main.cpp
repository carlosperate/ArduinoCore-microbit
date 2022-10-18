#include "Arduino.h"

// The micro:bit HAL global instance
MicroBit uBit;

// Initialise the global instances
arduino::Uart UART;

int main(void) {
    uBit.init();

    setup();

    for (;;) {
        loop();
    }

    return 0;
}
