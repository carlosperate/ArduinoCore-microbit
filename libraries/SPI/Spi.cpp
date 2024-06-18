#include "SPI.h"
#include "pins_arduino.h"

using namespace arduino;

SpiClass::SpiClass(uint8_t mosi, uint8_t miso, uint8_t sclk) {
    // TODO: convert from Arduino Pins to micro:bit HAL pins
    if (!isPinDigital(mosi) || !isPinDigital(miso) || !isPinDigital(sclk)) {
        codal::microbit_panic(MbArduinoPanic::INVALID_PIN);
    }
    this->mosi = mosi;
    this->miso = miso;
    this->sclk = sclk;
}

void SpiClass::begin() {
    if (this->codal_spi == NULL) {
        this->codal_spi =
            new codal::NRF52SPI(uBit.io.pin[mosi], uBit.io.pin[miso], uBit.io.pin[sclk]);
    }
}

void SpiClass::end() {
    if (this->codal_spi != NULL) {
        delete this->codal_spi;
        this->codal_spi = NULL;
    }
}

void SpiClass::beginTransaction(SPISettings settings) {
    if (this->codal_spi == NULL) {
        this->begin();
    }
    this->codal_spi->setFrequency(settings.getClockFreq());
    this->codal_spi->setMode(settings.getDataMode());
    BitOrder bit_order = settings.getBitOrder();
    if (bit_order != MSBFIRST) {
        // The micro:bit HAL only supports MSBFIRST
        codal::microbit_panic(MbArduinoPanic::NOT_COMPATIBLE_CONFIG);
    }
}

void SpiClass::endTransaction(void) {}

uint8_t SpiClass::transfer(uint8_t data) {
    int ret = this->codal_spi->write(data);
    return ret < 0 ? 0 : ret & 0xFF;
}

uint16_t SpiClass::transfer16(uint16_t data) {
    this->transfer(&data, 2);
    return data;
}

void SpiClass::transfer(void *buf, size_t count) {
    if (this->codal_spi == NULL) {
        this->begin();
    }

    // TODO: It's possible to set the receive buffer to be *buf as well, but
    //       lets first test it with an individual buffer and change it later
    // Allocate a temp receive buffer with the same size as the transmit buffer
    uint8_t *rx_buf = (uint8_t *)malloc(count);
    if (rx_buf == NULL) {
        // A mem allocation error will automatically panic, but just in case
        codal::microbit_panic(DEVICE_OOM);
    }

    int ret = this->codal_spi->transfer((uint8_t *)buf, count, rx_buf, count);
    if (ret < 0) {
        // There was an error with the transfer, so clear the data read back
        memset(buf, 0, count);
    } else {
        // Copy the received data back into the transmit buffer
        memcpy(buf, rx_buf, count);
    }
    free(rx_buf);
}

// There isn't a way to use interrupts with the micro:bit HAL, so these
// methods don't need to be implemented.
void SpiClass::usingInterrupt(int interruptNumber) {
    (void)interruptNumber;
}
void SpiClass::notUsingInterrupt(int interruptNumber) {
    (void)interruptNumber;
}

// These Arduino methods are deprecated and don't need an implementation.
void SpiClass::attachInterrupt() {}
void SpiClass::detachInterrupt() {}

SpiClass SPI(15, 14, 13);
