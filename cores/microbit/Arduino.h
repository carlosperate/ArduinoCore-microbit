#pragma once

#include "api/ArduinoAPI.h"
#include "microbit_hal.h"
#include "Uart.h"

// Declare the global objects
extern arduino::Uart UART;
#define Serial UART


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/* sketch */
void setup( void ) ;
void loop( void ) ;

#ifdef __cplusplus
} // extern "C"
#endif
