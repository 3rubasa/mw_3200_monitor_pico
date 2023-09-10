/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "i2c.h"
#include <iostream>
#include "constants.h"
#include "device.h"
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


int main() {
    stdio_init_all();
    initialize_i2c();

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
    ssi_init(std::shared_ptr<IDevice>{new Device{}}); 
    printf("SSI Handler initialised\n");

    while(true) {
        sleep_ms(60000);
    }
}