#pragma once
#include <cstdint>
#include "interfaces.h"
#include <memory>

class CPF8591Device : public ICPF8591Device {
public:
    CPF8591Device(std::shared_ptr<II2CNode> i2cNode, float refV, uint8_t chan);

    virtual float readVoltage() override;
    virtual void writeVoltage(float voltage) override;

private:
    std::shared_ptr<II2CNode> m_i2cNode;
    float m_refV;
    uint8_t m_chan;
};