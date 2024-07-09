#include <pins_arduino.h>
#include "api/Common.h"
#include "microbit_hal.h"

// Default configuration for compatibility with old Arduino Cores and sketches
static int _analogWriteResolution = 8;

/**
 * Read the analog value from a pin.
 *
 * The microcontroller on the micro:bit V2 has a 12 bit ADC, but for V1
 * compatibility the HAL is configured to 10 bit by default.
 *
 * @warning `OUTPUT_OPENDRAIN` is not implemented.
 *
 * @param pinNumber The Arduino pin to configure.
 * @param pinMode The mode to set the pin.
 */
int analogRead(pin_size_t pinNumber) {
    if (!isPinAnalog(pinNumber)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }

    // micro:bit HAL also reads a 10-bit value like Arduino
    return uBit.io.pin[pinNumber].getAnalogValue();
}

/**
 * Configure the ADC resolution.
 *
 * The micro:bit V1 hardware is only 10-bit capable, V2 has a 12-bit ADC, but
 * for compatibility with V1, the HAL is configured to 10-bit only by default.
 *
 * TODO: Check if there is a way to change the resolution in the V2 HAL.
void analogReadResolution(int resolution) {}
*/

/**
 * Configure the ADC voltage reference.
 *
 * TODO: analogReference will not be implemented at the moment as there isn't
 *       a direct mapping to the micro:bit HAL and we would need to bypass it.
void analogReference(uint8_t mode) {}
*/

/**
 * Output a PWM signal to a pin.
 *
 * TODO: Figure out and list here the micro:hal HAL PWM frequency.
 *
 * Some Arduino Cores only have PWM available in some pins, the micro:bit
 * can output PWM to any pin.
 *
 * Some Arduino Cores have a DAC and this function uses that feature as well,
 * however there is no DAC in the micro:bit microcontroller, so this will
 * always generate a PWM signal.
 *
 * @param pinNumber Any Arduino digital pin number to output the PWM signal.
 * @param value The duty cycle for the PWM signal, from 0 to 255 by default,
 *              unless the resolution has been changed by the
 *              analogWriteResolution() function.
 */
void analogWrite(pin_size_t pinNumber, int value) {
    if (!isPinPwm(pinNumber)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }

    // micro:bit HAL generates a 10-bit PWM as the default
    int microbit_hal_value = value;
    if (_analogWriteResolution > 10) {
        microbit_hal_value = microbit_hal_value >> (_analogWriteResolution - 10);
    } else if (_analogWriteResolution < 10) {
        microbit_hal_value = microbit_hal_value << (10 - _analogWriteResolution);
    }
    uBit.io.pin[pinNumber].setAnalogValue(microbit_hal_value);
}

/**
 * Configure the PWM resolution.
 *
 * For compatibility with older Arduino Cores, the PWM resolution is configured
 * to 8-bits by default.
 *
 * The micro:bit HAL requires a 10-bit value, so if the resolution set here is
 * higher than 10, the analogWrite() function will discard the extra bits.
 * If lower, it will pad the value with zeros.
 *
 * @param resolution The number of bits for the PWM/DAC resolution,
 *                   from 1 to 32. Out of range values are clamped.
 */
void analogWriteResolution(int resolution) {
    if (resolution < 1) {
        resolution = 1;
    } else if (resolution > 32) {
        resolution = 32;
    }
    _analogWriteResolution = resolution;
}
