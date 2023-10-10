#pragma once

#include "include/interfaces.h"
#include "interfaces.h"
#include <memory>
#include <string>

class GetStateHandler : public mw_tools::servers::ISSIHandler {
public:
    GetStateHandler(std::shared_ptr<IMWPBU3200Device> device);

    virtual std::string ProcessRequest();
private:
    std::shared_ptr<IMWPBU3200Device> m_device;
};