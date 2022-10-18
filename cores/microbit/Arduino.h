#pragma once

// Common API from Arduino
#include "api/ArduinoAPI.h"
// This core drivers
#include "Uart.h"
// The micro:bit HAL so that setup/loop can use the uBit object
#include "microbit_hal.h"

// Declare the global objects
extern arduino::Uart UART;
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
