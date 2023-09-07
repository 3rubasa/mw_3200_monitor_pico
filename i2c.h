#pragma once

#include <cstdint>

void initialize_i2c();
uint16_t ReadWord(uint8_t command);
uint8_t ReadByte(uint8_t command);