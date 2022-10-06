#ifndef Arduino_h
#define Arduino_h

#include "api/ArduinoAPI.h"

#include "MicroBit.h"

extern MicroBit uBit;

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/* sketch */
void setup( void ) ;
void loop( void ) ;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // Arduino_h
