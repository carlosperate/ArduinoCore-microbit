# Arduino Core for the BBC micro:bit

This is an Arduino Core for the BBC micro:bit built on top of the DAL/CODAL
C++ HAL (Hardware Abstraction Layer).

This enables the usage of Arduino IDE and Arduino libraries, together with
the DAL/CODAL `uBit` object API:
https://lancaster-university.github.io/microbit-docs/


## BBC micro:bit Hardware Abstraction Layers

The HAL for the BBC micro:bit V1 is called
[DAL (Device Abstraction Layer)](https://github.com/lancaster-university/microbit-samples/),
and the micro:bit V2 uses its successor
[CODAL (Component Oriented Device Abstraction Layer)](https://github.com/lancaster-university/microbit-v2-samples/),
which has a compatible user API.

This project is still in early stages and will first implement the micro:bit V2
CODAL version, with the aim to add micro:bit V1 DAL compatibility in the future.


## Installing this Arduino Core

As this Arduino Core is still in development, normal installation
instructions would only include a minimal non-functional core.
This minimal core at the moment is mostly used to install the tools and
then be replaced with a development version.

1. Add this URL to the `Arduino IDE Settings` > `Additional Board Manager URLs`:
    ```
    https://carlosperate.github.io/ArduinoCore-microbit/package_carlosperate_microbit_index.json
    ```
2. Install the "BBC micro:bit boards" core from the Arduino IDE Boards Manager.
3. Ensure the Arduino IDE is closed.
4. Find the Arduino `SKETCHBOOK` directory, which is Operating System dependent:
    - Windows: `%USERPROFILE%\Documents\Arduino`
    - macOS: `~/Documents/Arduino`
    - Linux: `~/Arduino`
5. We have two options to add this Arduino Core into the sketchbook.
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
6. Reopen the Arduino IDE


## Arduino IDE minimum version

Some of the features used in this template are not available in earlier version
of the Arduino IDE, so the currently minimum version is:

- 1.6.6
  - This needs to be confirmed


## Feature List

This is a list to indicate what has been implemented so far from the
official Arduino reference API https://www.arduino.cc/reference/en/ :

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
- [ ] `analogWriteResolution()`
    - Should set the PWM resolution (currently fixed 10-bit)

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
- [x] `isHexadecimalDigit()` via ArduinoCore-API
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
- [x] `usingInterrupt()` (blank implementation as it's not needed)
- [x] `notUsingInterrupt()` (blank implementation as it's not needed)
- [N/A] `setBitOrder()` (Deprecated by Arduino, should use SPISettings instead)
- [N/A] `setClockDivider()` (Deprecated by Arduino, should use SPISettings instead)
- [N/A] `setDataMode()` (Deprecated by Arduino, should use SPISettings instead)

### Wire
The Wire/TwoWire/I2C library has been created, but it is currently untested.

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

### Print
Abstract base class providing the print interface for `Serial`, `Wire`, `SPI`,
and other output classes.

- [x] `write()` via ArduinoCore-API
- [x] `print()` via ArduinoCore-API
- [x] `println()` via ArduinoCore-API
- [x] `flush()` via ArduinoCore-API

### Stream
Abstract base class extending `Print` for character-based streams (`Serial`,
`Wire`, etc.).

- [x] `available()` (implemented by the derived classes)
- [x] `read()` (implemented by the derived classes)
- [x] `peek()` (implemented by the derived classes)
- [x] `flush()` (inherited from `Print`)
- [x] `find()` via ArduinoCore-API
- [x] `findUntil()` via ArduinoCore-API
- [x] `parseInt()` via ArduinoCore-API
- [x] `parseFloat()` via ArduinoCore-API
- [x] `readBytes()` via ArduinoCore-API
- [x] `readBytesUntil()` via ArduinoCore-API
- [x] `readString()` via ArduinoCore-API
- [x] `readStringUntil()` via ArduinoCore-API
- [x] `setTimeout()` via ArduinoCore-API
- [x] `getTimeout()` via ArduinoCore-API

### USB
There is no direct USB access from the microcontroller running the Arduino code
(USB functionality is in a different on-board microcontroller), so this is
out of scope:
- [N/A] `Keyboard`
- [N/A] `Mouse`

### WiFi
There is no on-board WiFi hardware on the micro:bit, so this is out of scope.

### Constants
- [x] `HIGH` / `LOW` via ArduinoCore-API
- [x] `INPUT` / `OUTPUT` / `INPUT_PULLUP` via ArduinoCore-API
- [x] `LSBFIRST` / `MSBFIRST` via ArduinoCore-API
- [N/A] `LED_BUILTIN`
    - Not defined; the micro:bit has a 5x5 LED matrix instead of a single LED

### Data Types
Only the Arduino-specific data types are listed here. The other types listed
in the Arduino Language Reference (`int`, `char`, `float`, ...) are provided
by the compiler.

- [x] `String` via ArduinoCore-API
- [x] `boolean` via ArduinoCore-API
- [x] `byte` via ArduinoCore-API
- [x] `word` via ArduinoCore-API

### Utilities
- [ ] `PROGMEM`

### Other undocumented features
- [ ] `portOutputRegister`
- [ ] `portInputRegister`
- [ ] `portModeRegister`
- [ ] `digitalPinHasPWM`
- [ ] `attachInterruptParam()` (declared via ArduinoCore-API, implementation in core)
- [x] `yield()` (declared via ArduinoCore-API, implementation in core)
- [x] `isPinDigital()` / `isPinAnalog()` / `isPinPwm()` (micro:bit variant helpers)
- [x] `Printable` (class provided via ArduinoCore-API; not in the reference docs)


## License

This project is licensed under the [GNU LGPL v2.1 or later](LICENSE).

Vendored/bundled code keeps its own upstream license:
- `cores/microbit/api/` (ArduinoCore-API): LGPL 2.1 or later
- CODAL projects `codal-microbit-v2`, `codal-core`, `codal-nrf52`,
  vendored and modified files in `system/codal/` and `system/codal/utils/`: MIT
- `system/codal/libraries/codal-microbit-nrf5sdk`: Nordic Semiconductor
  modified BSD license
