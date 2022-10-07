#pragma once

#include "api/HardwareSerial.h"

namespace arduino {

class Uart : public HardwareSerial {
    public:
        Uart();
        void begin(const unsigned long baudrate);
        void begin(const unsigned long baudrate, const uint16_t config);
        void end();
        int available();
        int peek();
        int read();
        void flush();
        size_t write(const uint8_t c);
        size_t write(const uint8_t* str, const size_t size);
        using Print::write; // Take the Print write(const char *str)
        operator bool();
};

}  // namespace arduino
