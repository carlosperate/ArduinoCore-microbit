#include "Arduino.h"

// The micro:bit HAL global instance
codal::MicroBit uBit;

// This function can be overwritten by the variant-specific code
void initVariant() __attribute__((weak));
void initVariant() {}

/**
 * Initialise the micro:bit HAL, and everything needed by the Arduino Core.
 */
void init() {
    uBit.init();
    // The Arduino API expects random to be unseeded by default, and the user
    // sketches should call randomSeed(), or the sequence of values returned
    // by random() will be the same on every startup.
    // The micro:bit HAL randomly seeds on uBit.init(), so we need to undo it.
    randomSeed(0x12345678);
}

int main(void) {
    init();
    initVariant();

    setup();

    for (;;) {
        loop();

        // User defined function in a sketch to run after every loop iteration
        if (arduino::serialEventRun) arduino::serialEventRun();
    }

    return 0;
}
