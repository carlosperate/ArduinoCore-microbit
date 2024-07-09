#include "api/Common.h"
#include "microbit_hal.h"

/**
 * Wait for a given amount of time.
 *
 * The CODAL call yields to other fibers while waiting.
 * Even if the Arduino core does not create multiple fibers, multiple
 * micro:bit features depend on the CODAL scheduler to execute code while
 * idle during a yield.
 * The downside is that it has a time resolution of 4 ms,
 * and depends on other fibers/idle-tasks cooperating.
 *
 * @param ms Time to wait in milliseconds.
 */
void delay(unsigned long ms) {
    uBit.sleep(ms);
}

/**
 * Like delay(), with with microseconds instead of milliseconds.
 *
 * The CODAL call is a busy wait with a timer based delay.
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
