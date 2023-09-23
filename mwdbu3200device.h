#pragma once
#include <cstdint>
#include "interfaces.h"
#include <memory>

class MWPBU3200Device : public IMWPBU3200Device {
public:
    MWPBU3200Device(std::shared_ptr<II2CNode> i2cNode);
    virtual float readVin() override;
    virtual float readVout() override;
    virtual float readIout() override;
    virtual float readTemp1() override;
    virtual float readFanSpeed1() override;
    virtual float readFanSpeed2() override;
    virtual uint16_t readStatusWord() override;
    virtual uint8_t readStatusVout() override;
    virtual uint8_t readStatusIout() override;
    virtual uint8_t readStatusInput() override;
    virtual uint8_t readStatusTemp() override;
    virtual uint8_t readStatusCml() override;
    virtual uint8_t readStatusMfrSpecific() override;
    virtual uint8_t readStatusFans_1_2() override;
    virtual float readIoutOvercurrent() override;

private:
    std::shared_ptr<II2CNode> m_i2cNode;
};