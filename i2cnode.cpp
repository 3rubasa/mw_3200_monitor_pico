
#include "i2cnode.h"
#include <iostream>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "constants.h"
#include "conversions.h"
#include <sstream>


I2CNode::I2CNode(i2c_inst_t *bus, uint baudrate, uint8_t address, uint sdaPin, uint sclPin) :
    m_bus(bus),
    m_baudrate(baudrate),
    m_address(address),
    m_sdaPin(sdaPin),
    m_sclPin(sclPin)
{}
    
void I2CNode::Init() {
    i2c_init(m_bus, 100 * 1000);
    gpio_set_function(m_sdaPin, GPIO_FUNC_I2C);
    gpio_set_function(m_sclPin, GPIO_FUNC_I2C);
    gpio_pull_up(m_sdaPin);
    gpio_pull_up(m_sclPin);
}

uint8_t I2CNode::ReadByte(uint8_t regAddr) {
    uint8_t result = 0;

    int ret = i2c_write_blocking (m_bus, m_address, &regAddr, sizeof(regAddr), true);
    //printf("Writing result: %d \n", ret);
    if (ret < (int)sizeof(regAddr)) {
        std::stringstream errss;
        errss << "Writing regAddr 0x" << std::hex << (int)regAddr << 
            " to device 0x" << std::hex << m_address << 
            " on bus 0x" << std::hex << m_bus->hw << 
            " failed with ret value = " << ret;
        std::cout << errss.str() << std::endl;
        throw std::runtime_error(errss.str().c_str());
    }

    ret = i2c_read_blocking (m_bus, m_address, (uint8_t*)&result, sizeof(result), false);
    if (ret < (int)sizeof(result)) {
        std::stringstream errss;
        errss << "Reading " << sizeof(result) << " bytes response to regAddr 0x" << std::hex << (int)regAddr << 
            " from device 0x" << std::hex << m_address << 
            " on bus 0x" << std::hex << m_bus->hw << 
            " failed with ret value = " << ret;
        std::cout << errss.str() << std::endl;
        throw std::runtime_error(errss.str().c_str());
    }

    //printf("RESULT=%d", result);

    return result;
}

uint16_t I2CNode::ReadWord(uint8_t regAddr) {
    uint16_t result = 0;

    //printf("ReadWord() called \n");

    int ret = i2c_write_blocking (m_bus, m_address, &regAddr, sizeof(regAddr), true);
    if (ret < (int)sizeof(regAddr)) {
        std::stringstream errss;
        errss << "Writing regAddr 0x" << std::hex << (int)regAddr << 
            " to device 0x" << std::hex << m_address << 
            " on bus 0x" << std::hex << m_bus->hw << 
            " failed with ret value = " << ret;

        std::cout << errss.str() << std::endl;
        throw std::runtime_error(errss.str().c_str());
    }

    //printf("Writing result: %d \n", ret);

    ret = i2c_read_blocking (m_bus, m_address, (uint8_t*)&result, sizeof(result), false);
    if (ret < (int)sizeof(result)) {
        std::stringstream errss;
        errss << "Reading " << sizeof(result) << " bytes response to regAddr 0x" << std::hex << (int)regAddr << 
            " from device 0x" << std::hex << m_address << 
            " on bus 0x" << std::hex << m_bus->hw << 
            " failed with ret value = " << ret;

        std::cout << errss.str() << std::endl;
        throw std::runtime_error(errss.str().c_str());
    }

    //printf("RESULT=%d", result);

    return result;
}

void I2CNode::WriteByte(uint8_t regAddr, uint8_t val) {
    uint8_t output[2];
    output[0] = regAddr;
    output[1] = val;

    uint8_t result = 0;

    int ret = i2c_write_blocking (m_bus, m_address, output, 2, true);
    printf("Writing result: %d \n", ret);
    if (ret < 2) {
        std::stringstream errss;
        errss << "Writing regAddr 0x" << std::hex << (int)regAddr << 
            " to device 0x" << std::hex << m_address << 
            " on bus 0x" << std::hex << m_bus->hw << 
            " failed with ret value = " << ret;
        std::cout << errss.str() << std::endl;
        throw std::runtime_error(errss.str().c_str());
    }

    // int ret = i2c_write_blocking (m_bus, m_address, &val, sizeof(val), true);
    // //printf("Writing result: %d \n", ret);
    // if (ret < (int)sizeof(val)) {
    //     std::stringstream errss;
    //     errss << "Writing byte 0x" << std::hex << (int)val << 
    //         " to device 0x" << std::hex << m_address << 
    //         " on bus 0x" << std::hex << m_bus->hw << 
    //         " failed with ret value = " << ret;
    //     std::cout << errss.str() << std::endl;
    //     throw std::runtime_error(errss.str().c_str());
    // }

    //printf("RESULT=%d", result);
}