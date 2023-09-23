#include "pcf8591device.h"
#include "conversions.h"
#include "constants.h"
#include "i2cnode.h"
#include <stdexcept>
#include <cmath>

#define REGISTER_BASE_ADDRESS 0x40

CPF8591Device::CPF8591Device(std::shared_ptr<II2CNode> i2cNode, float refV, uint8_t chan) :
    m_i2cNode(i2cNode),
    m_refV(refV),
    m_chan(chan)
{
    if (chan > 3) {
        throw std::runtime_error("CPF8591 channel must be between 0 and 3");
    }
}

float CPF8591Device::readVoltage() {
    uint8_t val = m_i2cNode->ReadByte(0x40 | m_chan);
    return (m_refV / 255) * val;
}

void CPF8591Device::writeVoltage(float voltage) {
    m_i2cNode->WriteByte(0x40, (uint8_t)round((255 / m_refV) * voltage) );
}