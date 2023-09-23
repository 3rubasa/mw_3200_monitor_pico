#pragma once

#include <cstdint>
#include "interfaces.h"
#include "i2cnode.h"
#include "hardware/i2c.h"

class I2CNode : public II2CNode{
    public:
    I2CNode(i2c_inst_t *bus, uint baudrate, uint8_t address, uint sdaPin, uint sclPin);
    virtual void Init() override;

    virtual uint16_t ReadWord(uint8_t regAddr) override;
    virtual uint8_t ReadByte(uint8_t regAddr) override;
    virtual void WriteByte(uint8_t regAddr, uint8_t val) override;

    private:
        i2c_inst_t *m_bus;
        uint m_baudrate;
        uint8_t m_address; 
        uint m_sdaPin;
        uint m_sclPin;
};