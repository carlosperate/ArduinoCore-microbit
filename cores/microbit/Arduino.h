#pragma once

#include <stdint.h>

// Common API from Arduino
#include "api/ArduinoAPI.h"
// Core driver
#include "Uart.h"
// Variant include for the board specific configuration
#include "variant.h"
// The micro:bit HAL so that setup/loop can use the uBit object
#include "microbit_hal.h"

using namespace arduino;

// The Serial API object has been created with the UART name
#define Serial UART

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// Sketch functions
void setup(void);
void loop(void);

#ifdef __cplusplus
}  // extern "C"
#endif
