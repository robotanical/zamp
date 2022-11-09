#pragma once

#include <iostream>
#include <string>
#include <dlfcn.h>
#include "Interp4Command.hh"

class LibInterface
{
private:

    void *_LibHandler;
    std::string _CmdName;
    Interp4Command *(*_pCreateCmd)(void);

public:
    ~LibInterface();
    int initialize(std::string libName);
    Interp4Command *CreateCmd();
};