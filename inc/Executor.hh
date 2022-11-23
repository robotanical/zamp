#ifndef EXECUTOR_HH
#define EXECUTOR_HH
#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Parser.hh"
#include "Set4LibInterfaces.hh"
#include "Configuration.hh"
#include <string>

class Executor
{
    public:
    Executor();
    ~Executor();
    int initialize(std::string cmdFName);
    int configure(std::string configFName);
    private:
    Parser _parser;
    Set4LibInterfaces _libs_handler;
    std::shared_ptr<Configuration> _config;
    Interp4Command *_command;
    std::istringstream _stream;
    std::string keyword;

};
#endif