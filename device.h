#pragma once
#include <cstdint>

float readVin();

float readVout();

float readIout();

float readTemp1();

float readFanSpeed1();

float readFanSpeed2();

uint16_t readStatusWord();

uint8_t readStatusVout();

uint8_t readStatusIout();

uint8_t readStatusInput();

uint8_t readStatusTemp();

uint8_t readStatusCml();

uint8_t readStatusMfrSpecific();

uint8_t readStatusFans_1_2();

float readIoutOvercurrent();

float readVoutTrim();