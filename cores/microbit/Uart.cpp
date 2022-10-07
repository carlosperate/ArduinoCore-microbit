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
    // TODO: Figure out what to do with config
    uBit.serial.setBaudrate(baudrate);
}

void Uart::end(void) {
    // TODO: Need to disable UART so that the pins can be used for something else
}

int Uart::available() {
    return uBit.serial.isReadable();
}

int Uart::peek() {
    // TODO: this
}

int Uart::read() {
    return uBit.serial.getc();
}

void Uart::flush() {
    // TODO: this
}

size_t Uart::write(const uint8_t c) {
    int response = uBit.serial.putc(c);
    return response == DEVICE_OK ? 1 : 0;
}

size_t Uart::write(const uint8_t* str, const size_t size) {
    int bytes_sent = uBit.serial.send((uint8_t*)str, size, SYNC_SPINWAIT);
    if (bytes_sent == MICROBIT_SERIAL_IN_USE || bytes_sent == MICROBIT_INVALID_PARAMETER) {
        return 0;
    }
    return bytes_sent;
}

Uart::operator bool() {
    // No init delay, always ready
    return true;
}

}  // namespace arduino
