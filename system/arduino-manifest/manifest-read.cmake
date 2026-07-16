# CMake script specific to this Arduino Core (not part of micro:bit HAL/CODAL).
#
# Consumes the "Arduino build manifest" written by manifest-write.cmake and
# adds its contents to the CODAL build:
#
# - Each src-*.txt entry is a source file the Arduino CLI detected (sketch
#   files and Arduino library files, e.g. libraries installed with the
#   Library Manager). They are appended to SOURCE_FILES, so they get
#   compiled into, and linked with, the main CODAL executable target exactly
#   like the sketch sources found via ARDUINO_SKETCH.
# - Each entry's include directories (the {includes} the Arduino CLI
#   computed for that file, honouring library layout rules such as legacy
#   utility/ folders) are attached as per-source-file INCLUDE_DIRECTORIES.
#   This is also what lets the sketch find headers of header-only libraries.
# - ldflags.txt carries {compiler.libraries.ldflags} ("precompiled" Arduino
#   library archives); its entries are appended to CODAL_DEPS so they end up
#   on the target_link_libraries() line.
#
# Included from the top-level CMakeLists.txt (Arduino Core Edit block) when
# the ARDUINO_LIBRARIES_MANIFEST cache variable is set; it must run before
# utils/cmake/buildtools/codal.cmake creates the executable target.
# Appends to SOURCE_FILES and CODAL_DEPS in the including scope.

# 3.15 needed for list(POP_FRONT)
cmake_minimum_required(VERSION 3.15)

if(NOT EXISTS "${ARDUINO_LIBRARIES_MANIFEST}")
    # Nothing recorded yet: e.g. the pre-build configure run of a clean
    # build, which happens before the Arduino CLI compile phase.
    return()
endif()

file(GLOB ARDUINO_MANIFEST_ENTRIES "${ARDUINO_LIBRARIES_MANIFEST}/src-*.txt")
foreach(MANIFEST_ENTRY ${ARDUINO_MANIFEST_ENTRIES})
    file(STRINGS "${MANIFEST_ENTRY}" ENTRY_LINES)
    list(POP_FRONT ENTRY_LINES ENTRY_SOURCE)
    if("${ENTRY_SOURCE}" STREQUAL "" OR NOT EXISTS "${ENTRY_SOURCE}")
        continue()
    endif()
    list(APPEND SOURCE_FILES "${ENTRY_SOURCE}")
    if(NOT "${ENTRY_LINES}" STREQUAL "")
        set_source_files_properties(
            "${ENTRY_SOURCE}" PROPERTIES INCLUDE_DIRECTORIES "${ENTRY_LINES}")
    endif()
endforeach()
# Sketch sources appear both here and in the ARDUINO_SKETCH glob
list(REMOVE_DUPLICATES SOURCE_FILES)

if(EXISTS "${ARDUINO_LIBRARIES_MANIFEST}/ldflags.txt")
    file(STRINGS "${ARDUINO_LIBRARIES_MANIFEST}/ldflags.txt" ARDUINO_LDFLAGS)
    foreach(ARDUINO_LDFLAG ${ARDUINO_LDFLAGS})
        if(NOT "${ARDUINO_LDFLAG}" STREQUAL "")
            list(APPEND CODAL_DEPS "${ARDUINO_LDFLAG}")
        endif()
    endforeach()
endif()
