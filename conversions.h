#pragma once

#include <stdio.h>

unsigned long lin16_to_fl32 (unsigned int lin16_mant, unsigned int lin16_exp);
float lin16_to_float (unsigned int lin16_mant, unsigned int vout_mode);

float lin11_to_float (unsigned int xin);