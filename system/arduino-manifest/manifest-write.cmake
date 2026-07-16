# CMake script specific to this Arduino Core (not part of micro:bit HAL/CODAL).
#
# Records one entry of the "Arduino build manifest": the list of source files
# (and their include paths) that the Arduino CLI would compile itself, but
# that this core delegates to the CODAL CMake build instead.
#
# platform.txt points the compile recipes here, so that for every sketch or
# library source file detected by the Arduino CLI we capture, into
# MANIFEST_DIR, the information the CODAL build needs to compile it:
#
#   cmake -DMANIFEST_DIR=<dir> -P manifest-write.cmake -- <source_file> {includes}
#
# The link recipe records {compiler.libraries.ldflags} (archives of
# "precompiled" Arduino libraries) the same way:
#
#   cmake -DMANIFEST_DIR=<dir> -DENTRY_TYPE=ldflags -P manifest-write.cmake -- {compiler.libraries.ldflags}
#
# manifest-read.cmake consumes MANIFEST_DIR during the CMake configure run
# that platform.txt performs in its post-link hook.

# 3.15 needed for list(POP_FRONT)
cmake_minimum_required(VERSION 3.15)

if(NOT DEFINED MANIFEST_DIR OR "${MANIFEST_DIR}" STREQUAL "")
    message(FATAL_ERROR "manifest-write.cmake: MANIFEST_DIR not set")
endif()

# Collect the unparsed arguments, i.e. everything after the "--" separator
set(ARGS "")
set(PAST_SEPARATOR FALSE)
math(EXPR LAST_ARG "${CMAKE_ARGC} - 1")
foreach(i RANGE 0 ${LAST_ARG})
    if(PAST_SEPARATOR)
        list(APPEND ARGS "${CMAKE_ARGV${i}}")
    elseif("${CMAKE_ARGV${i}}" STREQUAL "--")
        set(PAST_SEPARATOR TRUE)
    endif()
endforeach()

if("${ENTRY_TYPE}" STREQUAL "ldflags")
    # Written once, at the (otherwise no-op) Arduino link step, which runs
    # after all compile recipes and before the post-link hooks.
    string(REPLACE ";" "\n" CONTENT "${ARGS}")
    file(WRITE "${MANIFEST_DIR}/ldflags.txt" "${CONTENT}\n")
    return()
endif()

list(POP_FRONT ARGS SOURCE_FILE)
if("${SOURCE_FILE}" STREQUAL "")
    message(FATAL_ERROR "manifest-write.cmake: no source file argument after --")
endif()
# Normalise to forward slashes so entries compare equal to CMake glob results
file(TO_CMAKE_PATH "${SOURCE_FILE}" SOURCE_FILE)

# One file per source, named after the source path, so that parallel compile
# recipe invocations never write to the same file. Line 1 is the source path,
# every following line is one include directory.
string(SHA1 SOURCE_HASH "${SOURCE_FILE}")
set(CONTENT "${SOURCE_FILE}\n")
foreach(ARG ${ARGS})
    # Only -I flags are expected here; store them as plain directories
    string(REGEX REPLACE "^-I" "" INCLUDE_DIR "${ARG}")
    file(TO_CMAKE_PATH "${INCLUDE_DIR}" INCLUDE_DIR)
    string(APPEND CONTENT "${INCLUDE_DIR}\n")
endforeach()
file(WRITE "${MANIFEST_DIR}/src-${SOURCE_HASH}.txt" "${CONTENT}")
