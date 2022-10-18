#pragma once

#include "MicroBit.h"

extern MicroBit uBit;

/**
 * Error codes specific for this micro:bit Arduino Core.
 */
// TODO: When the core is more or less dne, reorganise these error codes
enum MbArduinoPanic {
    BASE = 300,
    NOT_IMPLEMENTED,
    INVALID_PIN,
};
