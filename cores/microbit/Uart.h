#pragma once

#include "api/HardwareSerial.h"

namespace arduino {

class Uart : public HardwareSerial {
  public:
    Uart();

    /**
     * Configure the UART to start operating with a given baud rate.
     *
     * By default configured with 8 bit words, no parity, and 1 stop bit.
     *
     * @param baudrate UART baud rate in bytes per second.
     * @param config TODO: Need to figure this one out.
     */
    void begin(const unsigned long baudrate);
    void begin(const unsigned long baudrate, const uint16_t config);

    /**
     * Disable the UART and free up the pins.
     */
    void end();

    /**
     * Get the number of bytes available to read from the RX buffer.
     *
     * @return Number of bytes available to read.
     */
    int available();

    /**
     * Get a copy of the next byte from the read (RX) buffer without
     * removing it.
     *
     * @return A copy of the next byte from the RX buffer, or -1 if there
     *         isn't data available.
     */
    int peek();

    /**
     * Get a single byte from the read (RX) buffer.
     *
     * @code
     * if (Serial.available() > 0) {
     *     int single_byte = Serial.read();
     * }
     * @endcode
     *
     * @return The next byte from the RX buffer, or -1 if there isn't any.
     */
    int read();

    /**
     * Blocks until all the serial data out (TX) is sent.
     */
    void flush();

    /**
     * Sends data out (TX).
     *
     * @param c A single charcter to send out.
     *
     * @param buf A byte array to send out.
     * @param size The size of the buf data array.
     *
     * @param str A string to send out
     */
    size_t write(const uint8_t c);
    size_t write(const uint8_t* buf, const size_t size);
    using Print::write;  // Take write(const char *str) from the Print class

    /**
     * Indicates if it Serial is ready.
     *
     * Can be used to wait until ready:
     * @code
     * Serial.begin(115200);
     * while (!Serial);
     * @endcode
     */
    operator bool();
};

}  // namespace arduino
