# Arduino Core for BBC micro:bit based on CODAL

This an Arduino Core for the BBC micro:bit using the official C++ HAL
(Hardware Abstraction Layer).

This enables the usage of Arduino IDE and Arduino libraries, together with
the DAL/CODAL `uBit` object API:
https://lancaster-university.github.io/microbit-docs/


## BBC micro:bit Hardware Abstraction Layers

The HAL for the BBC micro:bit V1 is called
[DAL (Device Abstraction Layer)](https://github.com/lancaster-university/microbit-samples/),
and the micro:bit V2 uses its successor 
[CODAL (Component Oriented Device Abstraction Layer)](https://github.com/lancaster-university/microbit-v2-samples/),
which has a compatible user API.

This project is still in early stages and will first be implemented using
CODAL for micro:bit V2, with the aim to add micro:bit V1 DAL compatibility
in the future.

## Installing this Arduino Core

As this Arduino Core is still in development, normal installation
instructions would only include a minimal non-functional core.
This minimal core at the moment is mostly used to install the tools and
then be replaced with a development version.

1. Run a static server from the repository:
    ```
    python -m http.server
    ```
2. Add this URL to the Arduino IDE Settings > Additional Board Manager URLS:
    ```
    http://localhost:8000/docs/package_carlosperate_microbit_index.json
    ```
3. Install the "BBC micro:bit boards" core from the Arduino IDE Boards Manager.
4. Ensure the Arduino IDE is closed.
5. Find the Arduino `SKETCHBOOK` directory, which is Operating System dependent:
    - Windows: `%USERPROFILE%\Documents\Arduino`
    - macOS: `~/Documents/Arduino`
    - Linux: `~/Arduino`
6. We have two options to add this Arduino Core into the sketchbook.
    1. Open the terminal at the `SKETCHBOOK` directory and git clone
    (with submodules) into this path:
        ```
        git clone https://github.com/carlosperate/ArduinoCore-microbit.git --recurse-submodules hardware/carlosperate/microbit/
        ```
    2. Clone the project in your preferred location, and then create a symlink:
        ```
        mkdir -p <sketchbook-path>/hardware/carlosperate
        ln -s <path-to-cloned-repo> <sketchbook-path>/hardware/carlosperate/microbit
        ```
7. Reopen the Arduino IDE


## Arduino IDE minimum version

Some of the features used in this template are not available in earlier version
of the Arduino IDE, so the currently minimum version is:

- 1.6.6
  - This needs to be confirmed

## Feature List

This is a list indicate what's been implemented so far, as listed in
https://www.arduino.cc/reference/en/ :

### Digital I/O
- [x] `digitalRead()`
- [x] `digitalWrite()`
- [x] `pinMode()`
    - `OUTPUT_OPENDRAIN` mode not implemented

### Analog I/O
- [x] `analogRead()`
- [ ] `analogReference()`
    - Empty function for now, will not be implement unless requested/necessary
- [x] `analogWrite()`

Extra Analog I/O (not available in all Arduino cores):
- [ ] `analogReadResolution()`
    - Will not be implement unless requested/necessary
- [NA] `analogWriteResolution()`
    - There is no DAC, so this function is not applicable

### Advanced I/O
- [x] `tone()` (untested)
- [x] `noTone()` (untested)
- [ ] `pulseIn()`
- [ ] `pulseInLong()`
- [ ] `shiftIn()`
- [ ] `shiftOut()`

### Time
- [x] `delay()`
- [x] `delayMicroseconds()`
- [x] `micros()`
- [x] `millis()`

### Math
- [?] `abs()`
- [x] `constrain()` via ArduinoCore-API
- [x] `map()` via ArduinoCore-API
- [x] `max()` via ArduinoCore-API
- [x] `min()` via ArduinoCore-API
- [?] `pow()` via ArduinoCore-API
- [x] `sq()` via ArduinoCore-API
- [?] `sqrt()`

### Trigonometry
- [?] `cos()`
- [?] `sin()`
- [?] `tan()`

### Characters
- [x] `isAlpha()` via ArduinoCore-API
- [x] `isAlphaNumeric()` via ArduinoCore-API
- [x] `isAscii()` via ArduinoCore-API
- [x] `isControl()` via ArduinoCore-API
- [x] `isDigit()` via ArduinoCore-API
- [x] `isGraph()` via ArduinoCore-API
- [x] `isHexadecimalDigit()`
- [x] `isLowerCase()` via ArduinoCore-API
- [x] `isPrintable()` via ArduinoCore-API
- [x] `isPunct()` via ArduinoCore-API
- [x] `isSpace()` via ArduinoCore-API
- [x] `isUpperCase()` via ArduinoCore-API
- [x] `isWhitespace()` via ArduinoCore-API

### Random Numbers
- [x] `random()`
- [x] `randomSeed()`

### Bits and Bytes
- [x] `bit()` via ArduinoCore-API
- [x] `bitClear()` via ArduinoCore-API
- [x] `bitRead()` via ArduinoCore-API
- [x] `bitSet()` via ArduinoCore-API
- [x] `bitWrite()` via ArduinoCore-API
- [x] `highByte()` via ArduinoCore-API
- [x] `lowByte()` via ArduinoCore-API

### External Interrupts
- [ ] `attachInterrupt()`
- [ ] `detachInterrupt()`

### Interrupts
- [ ] `interrupts()`
- [ ] `noInterrupts()`

### Serial
- [x] `if(Serial)`
- [x] `available()`
- [x] `availableForWrite()`
- [x] `begin()`
    - [x] `config` parameter (only `SERIAL_8N1` supported; other configs panic)
- [ ] `end()`
- [x] `find()` via ArduinoCore-API
- [x] `findUntil()` via ArduinoCore-API
- [x] `flush()`
- [x] `parseFloat()` via ArduinoCore-API
- [x] `parseInt()` via ArduinoCore-API
- [x] `peek()`
- [x] `print()` via ArduinoCore-API
- [x] `println()` via ArduinoCore-API
- [x] `read()`
- [x] `readBytes()` via ArduinoCore-API
- [x] `readBytesUntil()` via ArduinoCore-API
- [x] `readString()` via ArduinoCore-API
- [x] `readStringUntil()` via ArduinoCore-API
- [x] `setTimeout()` via ArduinoCore-API
- [x] `write()`
- [ ] `serialEvent()`
    - This might not be required? And might be deprecated?

### SPI
The SPI library has been created, but it is currently untested.

- [x] `SPISettings` via ArduinoCore-API
- [x] `begin()`
- [x] `beginTransaction()`
- [x] `endTransaction()`
- [x] `end()`
- [x] `transfer()`
- [x] `transfer16()`
- [x] `usingInterrupt()` (blank implementation as it's used it's not needed)
- [x] `notusingInterrupt()` (blank implementation as it's used it's not needed)
- [N/A] `setBitOrder()` (Deprecated by Arduino, should use SPISettings instead)
- [N/A] `setClockDivider()` (Deprecated by Arduino, should use SPISettings instead)
- [N/A] `setDataMode()` (Deprecated by Arduino, should use SPISettings instead)


### Wire
The Wire/TwoWrie/I2C library has been created, but it is currently untested.

- [x] `begin()`
- [x] `end()`
- [x] `requestFrom()`
- [x] `beginTransmission()`
- [x] `endTransmission()`
- [x] `write()`
- [x] `available()`
- [x] `read()`
- [x] `setClock()`

Wire/I2C peripheral mode is currently out of scope:
- [N/A] `onReceive()`
- [N/A] `onRequest()`

Extra Wire methods to configure a timeout (not available in all Arduino cores),
also out of scope as there is a built-in, non-configurable timeout already:
- [N/A] `setWireTimeout()`
- [N/A] `clearWireTimeoutFlag()`
- [N/A] `getWireTimeoutFlag()`

### USB
There is no direct USB access from the microcontroller running the Arduino code
(USB functionality is in a different on-board microcontroller), so this is
out of scope:
- [N/A] `Keyboard`
- [N/A] `Mouse`

### Utilities
- [ ] `PROGMEM`

### Other undocumented features
- [ ] `portOutputRegister`
- [ ] `portInputRegister`
- [ ] `portModeRegister`
- [ ] `digitalPinHasPWM`
- more?
