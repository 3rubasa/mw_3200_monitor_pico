#pragma once
#include <cstdint>

class II2CNode {
    public:
    virtual void Init() = 0;
    virtual uint8_t ReadByte(uint8_t regAddr) = 0;
    virtual uint16_t ReadWord(uint8_t regAddr) = 0;
    virtual void WriteByte(uint8_t regAddr, uint8_t val) = 0;
};

class IMWPBU3200Device {
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