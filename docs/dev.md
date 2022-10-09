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
    - commit [`c8ea3774dbbedbc24f1a5df37cc9b6a6993bf67d`](https://github.com/carlosperate/ArduinoCore-microbit/commit/c8ea3774dbbedbc24f1a5df37cc9b6a6993bf67d)
- Removed `api/depcreated/WString.h`, since `api/String.h` has already been
  renamed to `api/WString.h` in
  [e733d03ed4adff7a15ee31472b779651d06db400](https://github.com/carlosperate/ArduinoCore-microbit/commit/e733d03ed4adff7a15ee31472b779651d06db400).

### Considerations when updating ArduinoCore-API
- Ensure `String.h` is renamed to `WString.h` and remove `depreacted/WString.h`

## CODAL

The source code from the CODAL build system is added to the `system` directory.

All we really need are the CODAL CMake files and the CODAL dependencies repos
cloned into the `system/codal/libraries` directory, so unnecessary files have
been removed in (ab0aaff2e8f8848c73d8376702f469d5479aa20c)[https://github.com/carlosperate/ArduinoCore-microbit/commit/ab0aaff2e8f8848c73d8376702f469d5479aa20c]
and the submodules added in [xxxxxx](xxxxx).

### Modifications

CODAL modifications applied in commit
[6b45986fcf748e54e33ca5dad90708cfa4b6c2a6](https://github.com/carlosperate/ArduinoCore-microbit/commit/6b45986fcf748e54e33ca5dad90708cfa4b6c2a6):
- Changes to `codal.json` to point to source code in `cores/microbit/`
- Added flag to `codal.json` to be able to ignore more CODAL BLE files
- Comment out CMake code that created a `samples` folder
  and copied a sample into `source/main.cpp`
- Change hardcoded path from some output files from "{project_path}/build" to
  the CMake build directory (which can then be set via CLI with the `-B` flag)
- Changed the location of the generated `codal_extra_definitions.h` and
  `codal_extra_definitions_new.h` files to be the same as the CMake build
  output directory.
- Don't generate the `MICROBIT.bin` and `MICROBIT.hex` files via CMake
  as these files will be generated via the Arduino tooling in platform.txt
- Added additional source file paths to CMake build via CLI values
  `ARDUINO_SKETCH` & `ARDUINO_LIBRARIES`
- Created a `.patch` for the `codal-microbit-v2` submodule code that needs
  to be applied to be able to compile with the ArduinoCore-API sources.
    - One the changes is the `_GNU_SOURCE` define needed due to:
      https://github.com/arduino/ArduinoCore-API/issues/158

Other future changes will also be reflected here.

### Submodule Patch

A patch is needed for the `system/codal/libraries/codal-microbit-v2` submodule.

The instructions to apply it can be found in the
`system/codal/libraries/README.md` file.

### Considerations when updating CODAL

- Only update the `codal-microbit-v2` submodule to a tag
    - Update the other submodules to the versions listed in
      `codal-microbit-v2/blob/master/target-locked.json`.
    - Check if the patches listed in `system/codal/libraries/README.md` are
      still applicable, and update the patch if needed
- The CODAL CMake files from the `microbit-v2-samples` repo can be updated
  when any upstream changes are relevant to this Arduino Core. 
    - All the local CMake file changes are surrounded by a
      `TODO: (Arduino Core Edit)` comment, so make sure those changes are
       still applied.
    - We can ignore any changes from all the removed file.
    - Ensure `codal.json` has the application path to `../../cores/microbit/`
      folder and set the `DEVICE_BLE` config value to `0`.
    - This commit right now includes all changes to the original CODAL source:
      https://github.com/carlosperate/ArduinoCore-microbit/commit/6b45986fcf748e54e33ca5dad90708cfa4b6c2a6
