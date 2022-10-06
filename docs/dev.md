# Dev Documentation

## ArduinoCore-API

The ArduinoCore-API is the hardware independent layer for all Arduino cores:
https://github.com/arduino/ArduinoCore-API

This is a generic project that all Arduino Cores can leverage, and don't
need to maintain individually.

### Modifications to api code

We had to make some modifications to this project:
- Renamed `String.h` to `WString.h` to avoid clashes with standard library
  `#include <string.h>`
    - https://github.com/arduino/ArduinoCore-API/issues/37
    - commit `c8ea3774dbbedbc24f1a5df37cc9b6a6993bf67d`
