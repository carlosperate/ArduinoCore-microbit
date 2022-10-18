#pragma once

#include <stdint.h>
#include "api/Common.h"

// Pins 19 and 20 are reserved for I2C
#define PINS_TOTAL          17
#define PINS_DIGITAL        17


inline bool isPinDigital(pin_size_t pin)  __attribute__((always_inline));

inline bool isPinDigital(pin_size_t pin) {
    return (pin <= 16);
}
