
#include "i2c.h"
#include <iostream>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "constants.h"
#include "conversions.h"

#define I2C_BUS i2c0
#define DEVICE_ADDRESS 0x47
#define SDA_PIN 0
#define SCL_PIN 1

void initialize_i2c() {
    i2c_init(I2C_BUS, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

uint8_t ReadByte(uint8_t command) {
    uint8_t result = 0;

    int ret = i2c_write_blocking (I2C_BUS, DEVICE_ADDRESS, &command, sizeof(command), true);
    //printf("Writing result: %d \n", ret);
    if (ret < (int)sizeof(command)) {
        std::cout << "Writing command 0x" << std::hex << command << 
            " to device 0x" << std::hex << DEVICE_ADDRESS << 
            " on bus 0x" << std::hex << I2C_BUS->hw << 
            " failed with ret value = " << ret << std::endl;

        throw std::runtime_error("Writing command to i2c slave failed!");
    }

    ret = i2c_read_blocking (I2C_BUS, DEVICE_ADDRESS, (uint8_t*)&result, sizeof(result), false);
    if (ret < (int)sizeof(result)) {
        std::cout << "Reading " << sizeof(result) << " bytes response to command 0x" << std::hex << command << 
            " from device 0x" << std::hex << DEVICE_ADDRESS << 
            " on bus 0x" << std::hex << I2C_BUS->hw << 
            " failed with ret value = " << ret << std::endl;

        throw std::runtime_error("Reading response to command from i2c slave failed!");
    }

    //printf("RESULT=%d", result);

    return result;
}

uint16_t ReadWord(uint8_t command) {
    uint16_t result = 0;

    //printf("ReadWord() called \n");

    int ret = i2c_write_blocking (I2C_BUS, DEVICE_ADDRESS, &command, sizeof(command), true);
    if (ret < (int)sizeof(command)) {
        std::cout << "Writing command 0x" << std::hex << command << 
            " to device 0x" << std::hex << DEVICE_ADDRESS << 
            " on bus 0x" << std::hex << I2C_BUS->hw << 
            " failed with ret value = " << ret << std::endl;

        throw std::runtime_error("Writing command to i2c slave failed!");
    }

    //printf("Writing result: %d \n", ret);

    ret = i2c_read_blocking (I2C_BUS, DEVICE_ADDRESS, (uint8_t*)&result, sizeof(result), false);
    if (ret < (int)sizeof(result)) {
        std::cout << "Reading " << sizeof(result) << " bytes response to command 0x" << std::hex << command << 
            " from device 0x" << std::hex << DEVICE_ADDRESS << 
            " on bus 0x" << std::hex << I2C_BUS->hw << 
            " failed with ret value = " << ret << std::endl;

        throw std::runtime_error("Reading response to command from i2c slave failed!");
    }

    //printf("RESULT=%d", result);

    return result;
}


