#pragma once
#include <cstdint>

class IDevice {
    public:
    virtual float readVin() = 0;
    virtual float readVout() = 0;
    virtual float readIout() = 0;
    virtual float readTemp1() = 0;
    virtual float readFanSpeed1() = 0;
    virtual float readFanSpeed2() = 0;
    virtual uint16_t readStatusWord() = 0;
    virtual uint8_t readStatusVout() = 0;
    virtual uint8_t readStatusIout() = 0;
    virtual uint8_t readStatusInput() = 0;
    virtual uint8_t readStatusTemp() = 0;
    virtual uint8_t readStatusCml() = 0;
    virtual uint8_t readStatusMfrSpecific() = 0;
    virtual uint8_t readStatusFans_1_2() = 0;
    virtual float readIoutOvercurrent() = 0;
};