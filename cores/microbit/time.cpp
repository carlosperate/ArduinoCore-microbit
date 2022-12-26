#include "api/Common.h"
#include "microbit_hal.h"

/**
 * Wait for a given amount of time.
 *
 * The current implementation is a busy wait with a timer based delay.
 * uBit.sleep() could be used instead, but it has a time resolution of 4 ms,
 * and depends on other fibers cooperating.
 *
 * @param ms Time to wait in milliseconds.
 */
void delay(unsigned long ms) {
    codal::system_timer_wait_ms(ms);
}

/**
 * Like delay(), with with microseconds instead of milliseconds.
 *
 * @param us Time to wait in microseconds.
 */
void delayMicroseconds(unsigned int us) {
    codal::system_timer_wait_us(us);
}

/**
 * Get the number of milliseconds since the programme started running.
 *
 * TODO: Document how long it takes to overflow and the time resolution.
 *
 * @return Time elapsed since startup, in milliseconds.
 */
unsigned long millis() {
    return codal::system_timer_current_time();
}

/**
 * Get the number of microseconds since the programme started running.
 *
 * TODO: Document how long it takes to overflow and the time resolution.
 *
 * @return Time elapsed since startup, in microseconds.
 */
unsigned long micros() {
    return codal::system_timer_current_time_us();
}
