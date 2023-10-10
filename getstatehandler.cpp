
#include "getstatehandler.h"
#include <vector>
#include <string>

using namespace std;

struct Param {
    string name;
    string val;
};

GetStateHandler::GetStateHandler(shared_ptr<IMWPBU3200Device> device) :
    m_device(device) 
{}

std::string GetStateHandler::ProcessRequest() {
    std::string output;

    vector<Param> values;
    vector<string> errors;

    Param param {"",""};

    // readVin()
    param.name="vin";
    try {
        param.val = to_string(m_device->readVin());
        values.push_back(param);
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readVin() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readVout()
    param.name="vout";
    try {
        param.val = to_string(m_device->readVout());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readVout() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readIout()
    param.name="iout";
    try {
        param.val = to_string(m_device->readIout());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readIout() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readTemp1()
    param.name="temp1";
    try {
        param.val = to_string(m_device->readTemp1());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readTemp1() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readFanSpeed1()
    param.name="fan1";
    try {
        param.val = to_string(m_device->readFanSpeed1());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readFanSpeed1() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readFanSpeed2()
    param.name="fan2";
    try {
        param.val = to_string(m_device->readFanSpeed2());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readFanSpeed2() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readStatusWord() = 0;
    param.name="status_word";
    try {
        param.val = to_string(m_device->readStatusWord());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readStatusWord() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readStatusVout() = 0;
    param.name="status_vout";
    try {
        param.val = to_string(m_device->readStatusVout());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readStatusVout() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readStatusIout() = 0;
    param.name="status_iout";
    try {
        param.val = to_string(m_device->readStatusIout());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readStatusIout() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readStatusInput() = 0;
    param.name="status_input";
    try {
        param.val = to_string(m_device->readStatusInput());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readStatusInput() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readStatusTemp() = 0;
    param.name="status_temp";
    try {
        param.val = to_string(m_device->readStatusTemp());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readStatusTemp() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readStatusCml() = 0;
    param.name="status_cml";
    try {
        param.val = to_string(m_device->readStatusCml());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readStatusCml() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readStatusMfrSpecific() = 0;
    param.name="status_mfr_specific";
    try {
        param.val = to_string(m_device->readStatusMfrSpecific());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readStatusMfrSpecific() error: "} + ex.what()); 
    }
    values.push_back(param);

    // readStatusFans_1_2() = 0;
    param.name="status_fans_1_2";
    try {
        param.val = to_string(m_device->readStatusFans_1_2());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readStatusFans_1_2() error: "} + ex.what()); 
    }
    values.push_back(param);

    // virtual float readIoutOvercurrent() = 0;
    param.name="status_iout_oc";
    try {
        param.val = to_string(m_device->readIoutOvercurrent());
    } catch (const exception& ex) {
        param.val = "ERROR";
        errors.push_back(std::string{"readIoutOvercurrent() error: "} + ex.what()); 
    }
    values.push_back(param);

    output = string{"{"} + R"("values": {)"; 
    size_t counter = 0;
    for (const auto& v: values) {
        output += R"(")" + v.name + R"(":")" + v.val + R"(")";
        counter++;
        if (counter < values.size())
            output += ",";
    }

    output += string{"},"} + R"("errors": [)";
    counter = 0;
    for (const auto& e: errors) {
        output += R"(")" + e + R"(")";
        counter++;
        if (counter < errors.size())
            output += ",";
    }
    output += "]}";

    return output;
}