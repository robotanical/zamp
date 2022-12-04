#pragma once

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "LibInterface.hh"
#include "Interp4Command.hh"
#include <memory>
#include <vector>


class Set4LibInterfaces
{
private:
    std::map<std::string, std::shared_ptr<LibInterface>> _libs;

public:
    int initialize();
    int initialize(std::vector<std::string> lib_names);
    Interp4Command * getCommand(std::string keyword);
};