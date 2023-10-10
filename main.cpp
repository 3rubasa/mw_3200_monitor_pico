/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"


#include "creds.h"

#include "constants.h"
#include "mwdbu3200device.h"
#include "i2cnode.h"

#include "include/core.h"
#include "include/wifi.h"
#include "include/interfaces.h"
#include "include/ssiserver.h"

#include "getstatehandler.h"

#include <memory>

#define MW_DBU_3200_I2C_ADDRESS 0x47

int main() {
    mw_tools::core::Init();

    mw_tools::wifi::Connect(WIFI_SSID, WIFI_PASSWORD, 30000);
    printf("WIFI Connected! \n");

    std::shared_ptr<II2CNode> mwPbu3200i2cNode = std::shared_ptr<II2CNode>{
        new I2CNode{i2c0, 100000, MW_DBU_3200_I2C_ADDRESS, 0, 1}};
    mwPbu3200i2cNode->Init();

    std::shared_ptr<IMWPBU3200Device> device 
        = std::shared_ptr<IMWPBU3200Device>{new MWPBU3200Device{mwPbu3200i2cNode}};

    std::shared_ptr<mw_tools::servers::ISSIHandler> getStateHandler 
        = std::shared_ptr<mw_tools::servers::ISSIHandler>(new GetStateHandler{device});

    std::shared_ptr<mw_tools::servers::ISSIServer> ssiServer 
      = std::shared_ptr<mw_tools::servers::ISSIServer>(new mw_tools::servers::SSIServer());

    ssiServer->RegisterHandler("state", getStateHandler);
    ssiServer->Start();

    while(true) {
        sleep_ms(1000);
    }
}