#include "Uart.h"
#include "microbit_hal.h"

namespace arduino {

Uart::Uart() {
    // No need to initialise anything
}

void Uart::begin(const unsigned long baudrate) {
    uBit.serial.setBaudrate(baudrate);
}

void Uart::begin(const unsigned long baudrate, const uint16_t config) {
    uBit.serial.setBaudrate(baudrate);

    // The micro:bit microcontroller only supports 8 bit words
    if (!((config & SERIAL_DATA_MASK) & SERIAL_DATA_8)) {
        codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
    }

    // The micro:bit HAL only supports 1 stop bit
    if (!((config & SERIAL_STOP_BIT_MASK) & SERIAL_STOP_BIT_1)) {
        codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
    }

    // The micro:bit HAL only supports no parity
    if (!((config & SERIAL_PARITY_MASK) & SERIAL_PARITY_NONE)) {
        codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
    }
}

void Uart::end(void) {
    // TODO: Need to disable UART so that the pins can be used for something else
}

int Uart::available() {
    return uBit.serial.isReadable();
}

int Uart::peek() {
    // TODO: this
    codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
    return 0;
}

int Uart::read() {
    int c = uBit.serial.getc();
    // All micro:bit hal error responses as negative values (so less than 0 [DEVICE_OK])
    return c < MICROBIT_OK ? -1 : c;
}

void Uart::flush() {
    // TODO: this
    codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
}

size_t Uart::write(const uint8_t c) {
    int response = uBit.serial.putc(c);
    return response == DEVICE_OK ? 1 : 0;
}

size_t Uart::write(const uint8_t* buf, const size_t size) {
    int bytes_sent = uBit.serial.send((uint8_t*)buf, size, SYNC_SPINWAIT);
    // Any error response will be a negative value
    return bytes_sent < 0 ? 0 : bytes_sent;
}

Uart::operator bool() {
    // No init delay, always ready
    return true;
}

}  // namespace arduino
