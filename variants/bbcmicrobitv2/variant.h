#pragma once

#include <stdint.h>
#include "api/Common.h"

// Pins 19 and 20 are reserved for I2C
#define PINS_TOTAL          17
#define PINS_DIGITAL        17
#define PINS_ANALOG          5

static const uint8_t A0 = 0;
static const uint8_t A1 = 1;
static const uint8_t A2 = 2;
static const uint8_t A3 = 3;
static const uint8_t A4 = 4;
static const uint8_t A5 = 10;


inline bool isPinDigital(pin_size_t pin)  __attribute__((always_inline));
inline bool isPinAnalog(pin_size_t pin)  __attribute__((always_inline));

inline bool isPinDigital(pin_size_t pin) {
    return (pin <= 16);
}

inline bool isPinAnalog(pin_size_t pin)  {
    return (pin <= 4) || (pin == 10);
}
