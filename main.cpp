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

#define WIFI_SSID "MTT"
#define WIFI_PASSWORD "pass1234"

#define DEBUG_printf printf

// enum class MESSAGE_COLOR {
//     Red,
//     Green,
//     Yellow
// };

// std::string FormatMessage(const std::string& message, MESSAGE_COLOR color) {
//     switch (color) {
//         case MESSAGE_COLOR::Red:
//             return std::string{"\033[1;31m"} + message + std::string{"\033[0m"};
//         break;
//         case MESSAGE_COLOR::Green:
//             return std::string{"\033[1;32m"} + message + std::string{"\033[0m"};
//         break;
//         case MESSAGE_COLOR::Yellow:
//             return std::string{"\033[1;33m"} + message + std::string{"\033[0m"};
//         break;
//         default:
//             return message;
//             break;
//     }
// }

// int print_read_vin(std::ostream& os);
// int print_read_vout(std::ostream& os);
// int print_read_iout(std::ostream& os);
// int print_read_temp_1(std::ostream& os);
// int print_read_fan_speed_1(std::ostream& os);
// int print_read_fan_speed_2(std::ostream& os);
// int print_status_word(std::ostream& os);
// void print_status_vout(std::ostream& os);
// void print_status_iout(std::ostream& os);
// void print_status_input(std::ostream& os);
// void print_status_temp(std::ostream& os);
// void print_status_cml(std::ostream& os);
// void print_status_mfr_specific(std::ostream& os);
// void print_status_fans_1_2(std::ostream& os);
// void print_read_iout_oc(std::ostream& os);


int main() {
    stdio_init_all();
    
     initialize_i2c();

    //     for (int i = 0; i < 10; i++) {
    //     printf("Sleeping 10 secs...\n");
    //     sleep_ms(1000);
    // }

    cyw43_arch_init();

    cyw43_arch_enable_sta_mode();

    // Connect to the WiFI network - loop until connected
    while(cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0){
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

    while(true);
    
//     for (int i = 0; i < 10; i++) {
//         printf("Sleeping 10 secs...\n");
//         sleep_ms(1000);
//     }

//     std::cout << "This was printed with STD COUT\n";

// // try {

//      while (true) {
//         std::stringstream sso;
//         try {

//         print_read_vin(sso);
//         print_read_vout(sso);
//         print_read_iout(sso);
//         print_read_temp_1(sso);
//         print_read_fan_speed_1(sso);
//         print_read_fan_speed_2(sso);

//         print_status_word(sso);
//         print_status_vout(sso);
//         print_status_iout(sso);
//         print_status_input(sso);
//         print_status_temp(sso);
//         print_status_cml(sso);
//         print_status_mfr_specific(sso);
//         print_status_fans_1_2(sso);
//         print_read_iout_oc(sso);
//         }
//         catch (std::runtime_error& ex) {
//             sso << "ERROR: " << ex.what() << std::endl;
//         }
        

//         sleep_ms(1000);

//         system("clear");
//         std::cout << sso.str();

//         //uint8_t cfg = devices[0]->readOnOffConfig(true);
//         //std::cout << std::endl << "ON_OFF_CONFIG: " << (int)(devices[0]->readOnOffConfig(true)) << std::endl;
//     }
// } catch (std::runtime_error& ex) {
//     std::cout << "EXCEPTION: " << ex.what();
// }

    // if (cyw43_arch_init()) {
    //     printf("Wi-Fi init failed");
    //     return -1;
    // }
    // while (true) {
    //     printf("Hello, world!\n");
    //     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    //     sleep_ms(250);
    //     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    //     sleep_ms(250);
    // }
}


// int print_read_vin(std::ostream& os) {
//     os << "VIN  = " << readVin() << " V AC NOTE: No reading below 10V"<< std::endl;
//     return 1;
// }

// int print_read_vout(std::ostream& os) {
//     os << "VOUT = " << readVout() << "V DC" << std::endl;
//     return 1;
// }
// int print_read_iout(std::ostream& os) {
//     os << "IOUT = " << readIout() << " A DC NOTE: No reading below 5.32Amp" << std::endl;
//     return 1;
// }
// int print_read_temp_1(std::ostream& os) {
//     os << "TEMP = " << readTemp1() << " Celsius NOTE: this is the temperature of the device" << std::endl;
//     return 1;
// }
// int print_read_fan_speed_1(std::ostream& os) {
//     os << "FAN1 = " << readFanSpeed1() << " RPM NOTE: No reading below 2000 RPM" << std::endl;
//     return 1;
// }
// int print_read_fan_speed_2(std::ostream& os) {
//     os << "FAN2 = " << readFanSpeed2() << " RPM NOTE: No reading below 2000 RPM" << std::endl;
//     return 1;
// }

// int print_status_word(std::ostream& os) {
//     //The STATUS_WORD command returns two bytes of information with a summary of the unit’s fault condition. 
//     // Based on the information in these bytes, the host can get more information by reading the appropriate status registers.

//     int lines_count = 0;
//     uint16_t status = readStatusWord();
//     os << "Status word: 0x" << std::hex << status << std::endl;
//     lines_count++;
//     if (status & 0x800)
//         os << FormatMessage("  Power NOT Good!", MESSAGE_COLOR::Red) << std::endl;
//     else 
//         os << FormatMessage("  Power Is Good!", MESSAGE_COLOR::Green) << std::endl;
//     lines_count++;

//     if (status & 0x2)
//       {os << "  FAULT: A communications, memory or logic fault has occurred!" << std::endl; lines_count++;}
//     if (status & 0x4)
//         {os << "  FAULT: A temperature fault or warning has occurred!" << std::endl;lines_count++;}
//     if (status & 0x8)
//         {os << "  FAULT: An input undervoltage fault has occurred!" << std::endl;lines_count++;}
//     if (status & 0x10)
//         {os << "  FAULT: An output overcurrent fault has occurred!" << std::endl;lines_count++;}
//     if (status & 0x20)
//         {os << "  FAULT: An output overvoltage fault has occurred!" << std::endl;lines_count++;}
//     if (status & 0x40)
//         {os << FormatMessage("  Unit is not providing power to the output, regardless of the reason, including simply not being enabled", MESSAGE_COLOR::Yellow) << std::endl;lines_count++;}
//     if (status & 0x80)
//         {os << "  Device was busy and unable to respond" << std::endl;lines_count++;}
//     if (status & 0x100)
//         {os << "  FAULT: UNKNOWN FAULT!" << std::endl;lines_count++;}
//     if (status & 0x200)
//         {os << "  STATUS_OTHER is set!" << std::endl;lines_count++;}
//     if (status & 0x400)
//         {os << "  FAULT: A fan or airflow fault or warning has occurred!" << std::endl;lines_count++;}
//     if (status & 0x1000)
//         {os << "  FAULT: A manufacturer specific fault or warning has occurred!" << std::endl;lines_count++;}
//     if (status & 0x2000)
//         {os << "  FAULT: An input voltage, input current, or input power fault or warning has occurred!" << std::endl;lines_count++;}
//     if (status & 0x4000)
//         {os << "  FAULT: An output current or output power fault or warning has occurred!" << std::endl;lines_count++;}
//     if (status & 0x8000)
//         {os << "  FAULT: An output voltage fault or warning has occurred!" << std::endl;lines_count++;}

//     return lines_count;
// }

// void print_status_temp(std::ostream& os){
//     uint8_t status = readStatusTemp();
//     os << "Status TEMP: 0x" << std::hex << (int)status << std::endl;
//     if (status & 0x10)
//         os << "  FAULT: Undertemperature fault!" << std::endl;
//     if (status & 0x20)
//         os << "  WARNING: Undertemperature Warning!" << std::endl;
//     if (status & 0x40)
//         os << "  WARNING: Overtemperature Warning!" << std::endl;
//     if (status & 0x80)
//         os << "  FAULT: Overtemperature Fault!" << std::endl;
// }

// void print_status_cml(std::ostream& os){
//     uint8_t status = readStatusCml();
//     os << "Status CML: 0x" << std::hex << (int)status << std::endl;
//     if (status & 0x1)
//         os << "  FAULT: Other Memory Or Logic Fault!" << std::endl;
//     if (status & 0x2)
//         os << "  FAULT: Other Communication Fault!" << std::endl;
//     if (status & 0x8)
//         os << "  FAULT: Processor Fault!" << std::endl;
//     if (status & 0x10)
//         os << "  FAULT: Memory fault!" << std::endl;
//     if (status & 0x20)
//         os << "  Packet Error Check Failed!" << std::endl;
//     if (status & 0x40)
//         os << "  Invalid Or Unsupported Data Received!" << std::endl;
//     if (status & 0x80)
//         os << "  Invalid Or Unsupported Command Received!" << std::endl;
// }
// void print_status_mfr_specific(std::ostream& os){
//     uint8_t status = readStatusMfrSpecific();
//     os << "Status MFR Specific: 0x" << std::hex << (int)status << std::endl;
// }
// void print_status_fans_1_2(std::ostream& os){
//     uint8_t status = readStatusFans_1_2();
//     os << "Status Fans_1_2: 0x" << std::hex << (int)status << std::endl;
//     if (status & 0x1)
//         os << "  WARNING: Airflow Warning!" << std::endl;
//     if (status & 0x2)
//         os << "  FAULT: Airflow Fault!" << std::endl;
//     if (status & 0x4)
//         os << "  Fan 2 Speed Overridden!" << std::endl;
//     if (status & 0x8)
//         os << "  Fan 1 Speed Overridden" << std::endl;
//     if (status & 0x10)
//         os << "  WARNING: Fan 2 Warning!" << std::endl;
//     if (status & 0x20)
//         os << "  WARNING: Fan 1 Warning!!" << std::endl;
//     if (status & 0x40)
//         os << "  FAULT: Fan 2 Fault!" << std::endl;
//     if (status & 0x80)
//         os << "  FAULT: Fan 1 Fault!" << std::endl;
// }

// void print_status_vout(std::ostream& os) {
//     uint8_t status = readStatusVout();
//     os << "Status VOUT: 0x" << std::hex << (int)status << std::endl;
//     if (status & 0x1)
//         os << "  VOUT Tracking Error!" << std::endl;
//     if (status & 0x2)
//         os << "  TOFF_MAX Warning!" << std::endl;
//     if (status & 0x4)
//         os << "  TON_MAX_FAULT!" << std::endl;
//     if (status & 0x8)
//         os << "  VOUT_MAX Warning (An attempt has been made to set the output voltage to value higher than allowed by the VOUT_MAX command (Section 13.5)." << std::endl;
//     if (status & 0x10)
//         os << "  FAULT: VOUT Undervoltage fault!" << std::endl;
//     if (status & 0x20)
//         os << "  WARNING: VOUT Undervoltage Warning!" << std::endl;
//     if (status & 0x40)
//         os << "  WARNING: VOUT Overvoltage Warning!" << std::endl;
//     if (status & 0x80)
//         os << "  FAULT: VOUT Overvoltage Fault!" << std::endl;
// }
// void print_status_iout(std::ostream& os){
//     uint8_t status = readStatusIout();
//     os << "Status IOUT: 0x" << std::hex << (int)status << std::endl;
//     if (status & 0x1)
//         os << "  WARNING: POUT Overpower Warning!" << std::endl;
//     if (status & 0x2)
//         os << "  FAULT: POUT Overpower Fault!" << std::endl;
//     if (status & 0x4)
//         os << "  Power Limiting! This bit is to be asserted when the unit is operating with the output in constant power mode at the power set by the POUT_MAX command (Section 14.2)." << std::endl;
//     if (status & 0x8)
//         os << "  FAULT: Current Share Fault! The conditions that cause the Current Share Fault bit to be set are defined by each device manufacturer." << std::endl;
//     if (status & 0x10)
//         os << "  FAULT: IOUT Undercurrent fault!" << std::endl;
//     if (status & 0x20)
//         os << "  WARNING: IOUT Overcurrent Warning!" << std::endl;
//     if (status & 0x40)
//         os << "  FAULT: IOUT overcurrent And Low Voltage Shutdown Fault!" << std::endl;
//     if (status & 0x80)
//         os << "  FAULT: IOUT Overcurrent Fault!" << std::endl;
// }
// void print_status_input(std::ostream& os){
//     uint8_t status = readStatusInput();
//     os << "Status INPUT: 0x" << std::hex << (int)status << std::endl;
//     if (status & 0x1)
//         os << "  WARNING: PIN Overpower Warning!" << std::endl;
//     if (status & 0x2)
//         os << "  WORNING: IIN Overcurrent Warning!" << std::endl;
//     if (status & 0x4)
//         os << "  FAULT: IIN Overcurrent Fault!" << std::endl;
//     if (status & 0x8)
//         os << "  Unit Is Off For Insufficient Input Voltage. Either the input voltage has never exceeded the input turn-on threshold (Section14.5)or if the unit did start, the input voltage decreased below the turn-off threshold (Section14.6)." << std::endl;
//     if (status & 0x10)
//         os << "  FAULT: VIN Undervaltage fault!" << std::endl;
//     if (status & 0x20)
//         os << "  WARNING: VIN Undervoltage Warning!" << std::endl;
//     if (status & 0x40)
//         os << "  WARNING: VIN Overvoltage Warning!" << std::endl;
//     if (status & 0x80)
//         os << "  FAULT: VIN Overvaltage Fault!" << std::endl;
// }

// void print_read_iout_oc(std::ostream& os){
//     os << "IOUT OC = " << readIoutOvercurrent() << " Amp" << std::endl;
// }