#include "device.h"
#include "conversions.h"
#include "constants.h"
#include "i2c.h"

float Device::readVin() {
    return lin11_to_float(ReadWord(READ_VIN));
}

float Device::readVout() {
    return lin16_to_float(ReadWord(READ_VOUT), (unsigned int)(VOUT_MODE_VAL & 0x1F));
}

float Device::readIout() {
    return lin11_to_float(ReadWord(READ_IOUT));
}

float Device::readTemp1() {
    return lin11_to_float(ReadWord(READ_TEMPERATURE_1));
}

float Device::readFanSpeed1() {
    return lin11_to_float(ReadWord(READ_FAN_SPEED_1));
}

float Device::readFanSpeed2() {
    return lin11_to_float(ReadWord(READ_FAN_SPEED_2));
}

uint16_t Device::readStatusWord() {
    return ReadWord(STATUS_WORD);
}

uint8_t Device::readStatusVout() {
    return ReadByte(STATUS_VOUT);
}

uint8_t Device::readStatusIout() {
    return ReadByte(STATUS_IOUT);
}

uint8_t Device::readStatusInput() {
    return ReadByte(STATUS_INPUT);
}

uint8_t Device::readStatusTemp() {
    return ReadByte(STATUS_TEMP);
}

uint8_t Device::readStatusCml() {
    return ReadByte(STATUS_CML);
}

uint8_t Device::readStatusMfrSpecific() {
    return ReadByte(STATUS_MFR_SPECIFIC);
}

uint8_t Device::readStatusFans_1_2() {
    return ReadByte(STATUS_FANS_1_2);
}

float Device::readIoutOvercurrent() {
    return lin11_to_float(ReadWord(IOUT_OC_FAULT_LIMIT));
}