#include "Executor.hh"

Executor::Executor()
{
    _config = std::make_shared<Configuration>();
}

Executor::~Executor()
{
    delete _command;
}

int Executor::initialize(std::string cmdFName){
    _parser.initialize(cmdFName.c_str());
    _parser.execPreprocessor(_stream);
    _libs_handler.initialize();
    return 0;
}

int Executor::configure(std:: string configFName){
    _parser.ReadFile(configFName.c_str(), _config);
    return 0;
}