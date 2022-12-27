#pragma once

// Common API from Arduino
#include "api/ArduinoAPI.h"
// This core drivers
#include "Uart.h"
// The micro:bit HAL so that setup/loop can use the uBit object
#include "microbit_hal.h"

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
