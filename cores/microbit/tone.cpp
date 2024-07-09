#include <pins_arduino.h>
#include "api/Common.h"
#include "microbit_hal.h"

#define TONE_TIMER_ID    71
#define TONE_TIMER_VALUE 1

static int current_tone_pin = -1;

static void timer_stop_tone(MicroBitEvent) {
    noTone(current_tone_pin);
}

/**
 * Generate a square wave on the specified pin & frequency at a 50% duty cycle.
 *
 * On micro:bit V2 the tone will also play through the built-in speaker.
 *
 * In the official API, only a single tone can be played at a time.
 * When this functions is called when a tone is already playing on a different
 * pin, then this function will have no effect. If the same pin is used, the
 * tone will be updated to the new frequency.
 *
 * To create multiple tones on different pins, the user must call noTone()
 * before calling tone() on a different pin.
 *
 * This function is non-blocking, so when called with a duration value, the
 * function will return immediately while the tone plays in the background.
 *
 * @param _pin The pin to output the tone.
 * @param frequency The frequency of the tone in Hz.
 * @param duration The duration of the tone in milliseconds.
 *                 If set to 0, the tone will play indefinitely or until
 *                 noTone() is called.
 *                 Optional argument with a default value of zero.
 */
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
    if (!isPinPwm(_pin)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }

    if (current_tone_pin != -1 && current_tone_pin != _pin) return;

    uBit.audio.enable();
    uBit.audio.setPin(uBit.io.pin[_pin]);
    if (frequency) {
        uBit.audio.virtualOutputPin.setAnalogPeriodUs(1000000 / frequency);
        uBit.audio.virtualOutputPin.setAnalogValue(127);
    } else {
        // Setting a frequency of 0 Hz should stop the tone
        uBit.audio.virtualOutputPin.setAnalogValue(0);
    }

    current_tone_pin = _pin;

    // Cancel any timer that might be running already
    uBit.timer.cancel(TONE_TIMER_ID, TONE_TIMER_VALUE);
    if (duration) {
        // Set a timer to stop the tone after the given time
        uBit.messageBus.listen(TONE_TIMER_ID, TONE_TIMER_VALUE, &timer_stop_tone);
        uBit.timer.eventAfter(duration, TONE_TIMER_ID, TONE_TIMER_VALUE);
    }
}

/**
 * Stop the generation of a tone on a pin.
 *
 * If the given pin is not playing a tone, or no tone is being played,
 * this function will have no effect.
 *
 * @param _pin The pin to stop playing the tone.
 */
void noTone(uint8_t _pin) {
    if (_pin != current_tone_pin) return;

    uBit.audio.virtualOutputPin.setAnalogValue(0);

    current_tone_pin = -1;
}
