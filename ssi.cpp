#include "ssi.h"
#include "interfaces.h"

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

shared_ptr<IDevice> g_device;
string g_output;

// SSI tags - tag length limited to 8 bytes by default
const char * ssi_tags[] = {"output"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen, u16_t part, u16_t* next_part) {
    printf("Handler called\n");
    printf("part=%d\n", part);
    printf("nextpart=%d\n", *next_part);

    struct Param {
        string name;
        string val;
    };

    if (part == 0) {
        vector<Param> values;
        vector<string> errors;

        Param param {"",""};

        // readVin()
        param.name="vin";
        try {
            param.val = to_string(g_device->readVin());
            values.push_back(param);
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readVin() error: "} + ex.what()); 
        }
        values.push_back(param);
        // readVout()
        param.name="vout";
        try {
            param.val = to_string(g_device->readVout());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readVout() error: "} + ex.what()); 
        }
        // readIout()
        param.name="iout";
        try {
            param.val = to_string(g_device->readIout());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readIout() error: "} + ex.what()); 
        }
        // readTemp1()
        param.name="temp1";
        try {
            param.val = to_string(g_device->readTemp1());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readTemp1() error: "} + ex.what()); 
        }
        // readFanSpeed1()
        param.name="fan1";
        try {
            param.val = to_string(g_device->readFanSpeed1());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readFanSpeed1() error: "} + ex.what()); 
        }
        // readFanSpeed2()
        param.name="fan2";
        try {
            param.val = to_string(g_device->readFanSpeed2());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readFanSpeed2() error: "} + ex.what()); 
        }
        // readStatusWord() = 0;
        param.name="status_word";
        try {
            param.val = to_string(g_device->readStatusWord());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readStatusWord() error: "} + ex.what()); 
        }
        // readStatusVout() = 0;
        param.name="status_vout";
        try {
            param.val = to_string(g_device->readStatusVout());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readStatusVout() error: "} + ex.what()); 
        }
        // readStatusIout() = 0;
        param.name="status_iout";
        try {
            param.val = to_string(g_device->readStatusIout());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readStatusIout() error: "} + ex.what()); 
        }
        // readStatusInput() = 0;
        param.name="status_input";
        try {
            param.val = to_string(g_device->readStatusInput());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readStatusInput() error: "} + ex.what()); 
        }
        // readStatusTemp() = 0;
        param.name="status_temp";
        try {
            param.val = to_string(g_device->readStatusTemp());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readStatusTemp() error: "} + ex.what()); 
        }
        // readStatusCml() = 0;
        param.name="status_cml";
        try {
            param.val = to_string(g_device->readStatusCml());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readStatusCml() error: "} + ex.what()); 
        }
        // readStatusMfrSpecific() = 0;
        param.name="status_mfr_specific";
        try {
            param.val = to_string(g_device->readStatusMfrSpecific());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readStatusMfrSpecific() error: "} + ex.what()); 
        }
        // readStatusFans_1_2() = 0;
        param.name="status_fans_1_2";
        try {
            param.val = to_string(g_device->readStatusFans_1_2());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readStatusFans_1_2() error: "} + ex.what()); 
        }
        // virtual float readIoutOvercurrent() = 0;
        param.name="status_iout_oc";
        try {
            param.val = to_string(g_device->readIoutOvercurrent());
        } catch (const exception& ex) {
            param.val = "ERROR";
            errors.push_back(std::string{"readIoutOvercurrent() error: "} + ex.what()); 
        }

        g_output = string{"{"} + R"("values": {)"; 
        size_t counter = 0;
        for (const auto& v: values) {
            g_output += R"(")" + v.name + R"(":")" + v.val + R"(")";
            counter++;
            if (counter < values.size())
                g_output += ",";
        }

        g_output += string{"},"} + R"("errors": [)";
        counter = 0;
        for (const auto& e: errors) {
            g_output += R"(")" + e + R"(")";
            counter++;
            if (counter < errors.size())
                g_output += ",";
        }
        g_output += "]}";
    }
    
  char toPrint[192];

  if (g_output.length() > 191+part*191) {
    *next_part = part+1;
    g_output.copy(toPrint, 191, part*191);
    toPrint[191]=0;
  } else {
    g_output.copy(toPrint, g_output.length()-part*191, part*191);
    toPrint[g_output.length()-part*191] =0;
  }

  size_t printed = snprintf(pcInsert, iInsertLen, toPrint);
  
  printf("IsertLen=%d\n", iInsertLen);
  return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init(shared_ptr<IDevice> device) {
    g_device=device;
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}