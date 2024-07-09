/**
 * @file wiring_digital.cpp
 * @brief Function definitions for setting pin mode, digital read and write.
 */
#include <pins_arduino.h>
#include "api/Common.h"
#include "microbit_hal.h"

/**
 * Set a pin to a specific mode (input or output).
 *
 * Input pull mode can also be enabled using this function.
 *
 * @warning `OUTPUT_OPENDRAIN` is not implemented.
 *
 * @param pinNumber The Arduino pin to configure.
 * @param pinMode The mode to set the pin.
 */
void pinMode(pin_size_t pinNumber, PinMode pinMode) {
    if (!isPinDigital(pinNumber)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }

    switch (pinMode) {
        case INPUT:
            // INPUT mode is meant to disable the pulls
            uBit.io.pin[pinNumber].setPull(codal::PullMode::None);
            // We do a dummy read to ensure the pin is internally configured as input
            (void)uBit.io.pin[pinNumber].getDigitalValue();
            break;
        case OUTPUT:
            if (!uBit.io.pin[pinNumber].isOutput()) {
                // Set the pin low to configure it internally as output.
                uBit.io.pin[pinNumber].setDigitalValue(0);
            }
            break;
        case INPUT_PULLUP:
            uBit.io.pin[pinNumber].setPull(codal::PullMode::Up);
            // We do a dummy read to ensure the pin is internally configured as input
            (void)uBit.io.pin[pinNumber].getDigitalValue();
            break;
        case INPUT_PULLDOWN:
            uBit.io.pin[pinNumber].setPull(codal::PullMode::Down);
            // We do a dummy read to ensure the pin is internally configured as input
            (void)uBit.io.pin[pinNumber].getDigitalValue();
            break;
        case OUTPUT_OPENDRAIN:
            // TODO: Not yet implemented, not sure if this is available in micro:bit HAL
        default:
            // Anything not implemented to raise a panic
            codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
            break;
    }
}

/**
 * Set a pin to a digital HIGH or LOW state.
 *
 * If the pin is configured as an input, this function will instead set the
 * pull up (HIGH) or down (LOW).
 *
 * @param pinNumber The Arduino pin number to write.
 * @param status The state to set the pin, either `HIGH` or `LOW`.
 */
void digitalWrite(pin_size_t pinNumber, PinStatus status) {
    if (!isPinDigital(pinNumber)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }

    // If the pin is configured as an input this function sets the pull
    if (uBit.io.pin[pinNumber].isInput()) {
        uBit.io.pin[pinNumber].setPull(status == LOW ? codal::PullMode::Down
                                                     : codal::PullMode::Up);
        return;
    }
    uBit.io.pin[pinNumber].setDigitalValue(status == LOW ? 0 : 1);
}

/**
 * Read the digital state of a pin.
 *
 * @param pinNumber The Arduino pin number to read.
 * @return The digital state of the pin, either `HIGH` or `LOW`.
 */
PinStatus digitalRead(pin_size_t pinNumber) {
    if (!isPinDigital(pinNumber)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }

    return uBit.io.pin[pinNumber].getDigitalValue() == 0 ? LOW : HIGH;
}
