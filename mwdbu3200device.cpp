#include "mwdbu3200device.h"
#include "conversions.h"
#include "constants.h"
#include "i2cnode.h"

MWPBU3200Device::MWPBU3200Device(std::shared_ptr<II2CNode> i2cNode) :
    m_i2cNode(i2cNode)
{}

float MWPBU3200Device::readVin() {
    return lin11_to_float(m_i2cNode->ReadWord(READ_VIN));
}

float MWPBU3200Device::readVout() {
    return lin16_to_float(m_i2cNode->ReadWord(READ_VOUT), (unsigned int)(VOUT_MODE_VAL & 0x1F));
}

float MWPBU3200Device::readIout() {
    return lin11_to_float(m_i2cNode->ReadWord(READ_IOUT));
}

float MWPBU3200Device::readTemp1() {
    return lin11_to_float(m_i2cNode->ReadWord(READ_TEMPERATURE_1));
}

float MWPBU3200Device::readFanSpeed1() {
    return lin11_to_float(m_i2cNode->ReadWord(READ_FAN_SPEED_1));
}

float MWPBU3200Device::readFanSpeed2() {
    return lin11_to_float(m_i2cNode->ReadWord(READ_FAN_SPEED_2));
}

uint16_t MWPBU3200Device::readStatusWord() {
    return m_i2cNode->ReadWord(STATUS_WORD);
}

uint8_t MWPBU3200Device::readStatusVout() {
    return m_i2cNode->ReadByte(STATUS_VOUT);
}

uint8_t MWPBU3200Device::readStatusIout() {
    return m_i2cNode->ReadByte(STATUS_IOUT);
}

uint8_t MWPBU3200Device::readStatusInput() {
    return m_i2cNode->ReadByte(STATUS_INPUT);
}

uint8_t MWPBU3200Device::readStatusTemp() {
    return m_i2cNode->ReadByte(STATUS_TEMP);
}

uint8_t MWPBU3200Device::readStatusCml() {
    return m_i2cNode->ReadByte(STATUS_CML);
}

uint8_t MWPBU3200Device::readStatusMfrSpecific() {
    return m_i2cNode->ReadByte(STATUS_MFR_SPECIFIC);
}

uint8_t MWPBU3200Device::readStatusFans_1_2() {
    return m_i2cNode->ReadByte(STATUS_FANS_1_2);
}

float MWPBU3200Device::readIoutOvercurrent() {
    return lin11_to_float(m_i2cNode->ReadWord(IOUT_OC_FAULT_LIMIT));
}