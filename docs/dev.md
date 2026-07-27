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
    - commit [c8ea377](https://github.com/carlosperate/ArduinoCore-microbit/commit/c8ea3774dbbedbc24f1a5df37cc9b6a6993bf67d)
- Removed `api/depcreated/WString.h`, since `api/String.h` has already been
  renamed to `api/WString.h` in
  [e733d03](https://github.com/carlosperate/ArduinoCore-microbit/commit/e733d03ed4adff7a15ee31472b779651d06db400).

### Considerations when updating ArduinoCore-API

- Ensure `String.h` is renamed to `WString.h` and remove `depreacted/WString.h`

## CODAL

The source code from the CODAL build system is added to the `system` directory.

All we really need are the CODAL CMake files and the CODAL dependencies repos
cloned into the `system/codal/libraries` directory, so unnecessary files have
been removed in
[ab0aaff](https://github.com/carlosperate/ArduinoCore-microbit/commit/ab0aaff2e8f8848c73d8376702f469d5479aa20c)
and the submodules added in
[6b45986](https://github.com/carlosperate/ArduinoCore-microbit/commit/6b45986fcf748e54e33ca5dad90708cfa4b6c2a6).

### Modifications

CODAL modifications applied in
[commit 6b45986](https://github.com/carlosperate/ArduinoCore-microbit/commit/6b45986fcf748e54e33ca5dad90708cfa4b6c2a6):
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
    - ~~One changes is the `_GNU_SOURCE` define needed due to:~~
      https://github.com/arduino/ArduinoCore-API/issues/158
        - This has been fixed in ArduinoCode-API release `1.4.0` and removed in
          [commit 728cdaf](https://github.com/carlosperate/ArduinoCore-microbit/commit/728cdafdef6b2f81654224d02ccc09dded291228).

Added in [commit b0104af](https://github.com/carlosperate/ArduinoCore-microbit/commit/b0104aff56a6925d4ffa8a72a56e53208904442a):
- Add Arduino variant folder path to the CMake file list of h and cpp files.

In [commit 2f2446d](https://github.com/carlosperate/ArduinoCore-microbit/commit/2f2446d695b213dfc1b2954df797ba1003ba54fd)
and [commit 9905ee1](https://github.com/carlosperate/ArduinoCore-microbit/commit/9905ee14c359238b6b25a697bfe3d530e301bbf2):
- Fixed how Arduino Core libraries are included in the build.
- Ensure C files (not just C++) in the sketch are compiled.

In [commit 059e0de](https://github.com/carlosperate/ArduinoCore-microbit/commit/059e0de735e618e8e77a0ccbaa0d09f3ee5b9759):
- Pass cli values to the CMake build to generate Arduino specific defines

In [commit 34280fd](https://github.com/carlosperate/ArduinoCore-microbit/commit/34280fdae45e9385e5cbb3bc435ab5517e57a53e):
- Updated CODAL from tag v0.2.43 to v0.2.67
- Updated microbit-v2-samples files from commit a38d392 to d59f07b
- Update codal.json config from `NO_BLE` to `DEVICE_BLE`

In [commit abe706697cdfbff6427ad311e7af58b6e2974d80](https://github.com/carlosperate/ArduinoCore-microbit/commit/abe706697cdfbff6427ad311e7af58b6e2974d80):
- Updated microbit-v2-samples files from commit [d59f07b](https://github.com/lancaster-university/microbit-v2-samples/commit/d59f07b),
  to [04b7089](https://github.com/lancaster-university/microbit-v2-samples/commit/04b7089d82af24534f3dcd460a9c343850b60b5d)
- No changes in the modifications applied so far.

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
- Diff the changes between the old and new versions of
  `codal-microbit-v2/target.json` and check if any changes there has an impact
  on platform.txt
    - Watch out for `show_size`, absent in v0.2.67, which is the only reason the
      size-reporting code vendored in `utils/cmake/` is currently inactive.
- The CODAL CMake files from the `microbit-v2-samples` repo can be updated
  when any upstream changes are relevant to this Arduino Core.
    - All the local CMake file changes are surrounded by a
      `TODO: (Arduino Core Edit)` comment, so make sure those changes are
       still applied.
    - We can ignore any changes from all the removed files.
    - Ensure `codal.json` has the application path to `../../cores/microbit/`
      folder and set the `DEVICE_BLE` config value to `0`.
