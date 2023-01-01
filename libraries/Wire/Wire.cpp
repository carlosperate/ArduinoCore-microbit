#include "Wire.h"
#include "microbit_hal.h"

namespace arduino {

TwoWire::TwoWire() {}

void TwoWire::begin() {
    // Nothing to do to configure the I2C controller
}

void TwoWire::begin(uint8_t address) {
    if (address != 0) {
        // I2C peripheral mode is not supported by the micro:bit HAL
        codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
    } else {
        begin();
    }
}

void TwoWire::end() {
    // There isn't a way in the micro:bit HAL to deinitialise I2C
    codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
}

size_t TwoWire::requestFrom(uint8_t address, size_t len) {
    return requestFrom(address, len, true);
}

size_t TwoWire::requestFrom(uint8_t address, size_t len, bool stopBit = true) {
    uint8_t tmp_buffer[WIRE_BUFFER_SIZE] = {0};
    len = codal::min(WIRE_BUFFER_SIZE, len);
    uint8_t address_8_bits = (address << 1) | 1;

    rx_buffer.clear();

    int read_state = uBit.i2c.read(address_8_bits, tmp_buffer, len, !stopBit);
    if (read_state != MICROBIT_OK) {
        return 0;
    }

    // Move the data to the RX ring buffer
    for (size_t i = 0; i < len; i++) {
        rx_buffer.store_char(tmp_buffer[i]);
    }

    return len;
}

void TwoWire::beginTransmission(uint8_t address) {
    peripheral_address = address;
    memset(tx_buffer, 0, WIRE_BUFFER_SIZE);
    tx_buffer_i = 0;
}

uint8_t TwoWire::endTransmission() {
    return endTransmission(true);
}

uint8_t TwoWire::endTransmission(bool stopBit) {
    int i2c_state = uBit.i2c.write(peripheral_address, tx_buffer, tx_buffer_i, !stopBit);
    if (i2c_state != MICROBIT_OK) {
        return 4;
    }
    return 0;
}

size_t TwoWire::write(uint8_t value) {
    if (tx_buffer_i >= WIRE_BUFFER_SIZE) return 0;
    tx_buffer[tx_buffer_i++] = value;
    return 1;
}

size_t TwoWire::write(const uint8_t *buffer, size_t size) {
    if (tx_buffer_i + size >= WIRE_BUFFER_SIZE) {
        size = WIRE_BUFFER_SIZE - tx_buffer_i;
    }
    memcpy(tx_buffer + tx_buffer_i, buffer, size);
    return size;
}

int TwoWire::available() {
    return rx_buffer.available();
}

int TwoWire::peek() {
    return rx_buffer.peek();
}

int TwoWire::read() {
    return rx_buffer.read_char();
}

void TwoWire::setClock(uint32_t freq) {
    uBit.i2c.setFrequency(freq);
}

void TwoWire::onReceive(void (*handler)(int)) {
    // There isn't a way in the micro:bit HAL to deinitialise I2C
    codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
}

void TwoWire::onRequest(void (*handler)(void)) {
    // There isn't a way in the micro:bit HAL to deinitialise I2C
    codal::microbit_panic(MbArduinoPanic::NOT_IMPLEMENTED);
}

}  // namespace arduino

arduino::TwoWire Wire;
