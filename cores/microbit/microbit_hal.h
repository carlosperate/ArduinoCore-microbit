#pragma once

#include "MicroBit.h"

extern codal::MicroBit uBit;

/**
 * codal-microbit-v2/inc/compat/MicroBitCompat.h defines SPI as NRF52SPI, which
 * clashes with the Arduino usage of the globally defied arduino::SPI instance
 */
#if defined(SPI)
#undef SPI
#endif

/**
 * Error codes specific for this micro:bit Arduino Core.
 */
// TODO: When the core is more or less dne, reorganise these error codes
enum MbArduinoPanic {
    BASE = 300,
    NOT_IMPLEMENTED,
    INVALID_PIN,
    NOT_COMPATIBLE_CONFIG,
};
