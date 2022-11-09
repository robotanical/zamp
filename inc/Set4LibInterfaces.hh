#pragma once

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "LibInterface.hh"
#include "Interp4Command.hh"
#include <memory>

class Set4LibInterfaces
{
private:
    std::map<std::string, std::shared_ptr<LibInterface>> _libs;

public:
    int initialize();
    Interp4Command * getCommand(std::string keyword);
};