#include "Uart.h"
#include "api/Common.h"
#include "microbit_hal.h"

namespace arduino {

Uart::Uart() {
    // No need to initialise anything
}

void Uart::begin(const unsigned long baudrate) {
    uBit.serial.setBaudrate(baudrate);
    // micro:bit HAL brings up the RX buffer + interrupts lazily on isReadable()/getc().
    // this->available() reads rxBufferedSize(), which does NOT trigger it.
    uBit.serial.isReadable();
}

void Uart::begin(const unsigned long baudrate, const uint16_t config) {
    // The micro:bit HAL only supports 8 bit words, no parity, and 1 stop bit (8N1).
    if ((config & SERIAL_DATA_MASK) != SERIAL_DATA_8 ||
        (config & SERIAL_STOP_BIT_MASK) != SERIAL_STOP_BIT_1 ||
        (config & SERIAL_PARITY_MASK) != SERIAL_PARITY_NONE) {
        codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
    }
    this->begin(baudrate);
}

void Uart::end(void) {
    // TODO: Need to disable UART so that the pins can be used for something else
}

int Uart::available() {
    // Include a possible byte from a previous peek()
    return uBit.serial.rxBufferedSize() + (peeked >= 0 ? 1 : 0);
}

int Uart::availableForWrite() {
    return uBit.serial.getTxBufferSize() - uBit.serial.txBufferedSize();
}

int Uart::peek() {
    // micro:bit HAL has no peek, so pull out one byte and cache it for read()
    if (peeked < 0) {
        peeked = uBit.serial.getc();
        if (peeked < MICROBIT_OK) {
            peeked = -1;
        }
    }
    return peeked;
}

int Uart::read() {
    // Return the byte stashed by a previous peek() before reading from the buffer
    if (peeked >= 0) {
        int c = peeked;
        peeked = -1;
        return c;
    }
    int c = uBit.serial.getc();
    // All micro:bit hal error responses as negative values (so less than 0 [DEVICE_OK])
    return c < MICROBIT_OK ? -1 : c;
}

void Uart::flush() {
    // Yield to the CODAL scheduler while the TX buffer drains instead of a busy wait.
    while (uBit.serial.txBufferedSize() > 0) {
        yield();
    }
}

size_t Uart::write(const uint8_t c) {
    int response = uBit.serial.putc(c);
    return response == DEVICE_OK ? 1 : 0;
}

size_t Uart::write(const uint8_t* buf, const size_t size) {
    int bytes_sent = uBit.serial.send((uint8_t*)buf, size, codal::SYNC_SPINWAIT);
    // Any error response will be a negative value
    return bytes_sent < 0 ? 0 : bytes_sent;
}

Uart::operator bool() {
    // No init delay, always ready
    return true;
}

}  // namespace arduino

// Initialise the global instance
arduino::Uart UART;
