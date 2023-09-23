/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "i2cnode.h"
#include <iostream>
#include "constants.h"
#include "mwdbu3200device.h"
#include "pcf8591device.h"
#include <sstream>
#include <memory>

#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt_priv.h"
#include "tusb.h"

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"

#include "ssi.h"
#include "creds.h"

#define DEBUG_printf printf
#define PCF8591_INPUT_CHAN 0
#define PCF8591_REF_V 5.2
#define MW_DBU_3200_I2C_ADDRESS 0x47
#define PCF8591_I2C_ADDRESS 0x48

int main() {
    stdio_init_all();

    std::shared_ptr<II2CNode> mwPbu3200i2cNode = std::shared_ptr<II2CNode>{
        new I2CNode{i2c0, 100000, MW_DBU_3200_I2C_ADDRESS, 0, 1}};
    mwPbu3200i2cNode->Init();

    std::shared_ptr<II2CNode> curControlNode = std::shared_ptr<II2CNode>{
        new I2CNode{i2c1, 100000, PCF8591_I2C_ADDRESS, 2, 3}};
    curControlNode->Init();

    cyw43_arch_init();

    cyw43_arch_enable_sta_mode();

    // Connect to the WiFI network - loop until connected
    // WIFI_SSID and WIFI_PASSWORD come from creds.h
    int err = 0;
    while((err = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) != 0){
        printf("Error while connecting: %d\n", err);
        if (err == PICO_ERROR_TIMEOUT) {
            printf("Probably SSID specified in creds.h %s was not found: \n", WIFI_SSID);
        } else if (err == PICO_ERROR_BADAUTH) {
            printf("Probably password specified in creds.h %s is incorrect: \n", WIFI_PASSWORD);
        }
        printf("Attempting to connect...\n");
    }
    // Print a success message once connected
    printf("Connected! \n");
    
    // Initialise web server
    httpd_init();
    printf("Http server initialised\n");

    // Configure SSI and CGI handler
    ssi_init(std::shared_ptr<IMWPBU3200Device>{new MWPBU3200Device{mwPbu3200i2cNode}}); 
    printf("SSI Handler initialised\n");


    auto adc = std::shared_ptr<ICPF8591Device>{
        new CPF8591Device{curControlNode, PCF8591_REF_V, PCF8591_INPUT_CHAN}};

    while(true) {
        sleep_ms(100);
        float input_signal = adc->readVoltage();
        printf("input_signal = %f\n", input_signal);
        // map Orion JR range [0;5] to dbu3200 range [1;4.7]
        float output_signal = 1 + input_signal * 0.74;
        printf("output_signal = %f\n", output_signal);
        adc->writeVoltage(output_signal);
    }

    while(true) {
        sleep_ms(60000);
    }
}