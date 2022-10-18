#include "api/Common.h"
#include "pins_arduino.h"

#include "microbit_hal.h"

int analogRead(pin_size_t pinNumber) {
    if (!isPinAnalog(pinNumber)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }

    // micro:bit HAL also reads a 10-bit value like Arduino
    return uBit.io.pin[pinNumber].getAnalogValue();
}

/**
 * TODO: This will not be implement at the moment as there isn't a direct
 *        mapping to micro:bit HAL and we would need to bypass it.
void analogReference(uint8_t mode) {
    ;
}
*/

void analogWrite(pin_size_t pinNumber, int value) {
    if (!isPinAnalog(pinNumber)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }

    // micro:bit HAL also generates a 10-bit PWM value like Arduino
    uBit.io.pin[pinNumber].setAnalogValue(value);
}
