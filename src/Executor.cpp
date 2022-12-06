#include "Executor.hh"

Executor::Executor(Scene &scene) : _scene(scene) {
  _config = std::make_shared<Configuration>(_scene);
  //   client client(_scene);
}

Executor::~Executor() { delete _command; }

int Executor::initialize(std::string cmdFName) {
  std::string key;
  _parser.initialize(cmdFName.c_str());
  _parser.execPreprocessor(_stream);
  while(_stream >> key)
  {
    _command = _libs_handler.getCommand(key);
    _command->ReadParams(_stream);
    _command->ExecCmd(_scene, _client);
    
  }
  return 0;
}

int Executor::configure(std::string configFName) {
  _parser.ReadFile(configFName.c_str(), _config);
  _libs_handler.initialize(_config->getLibNames());
  _client.openConnection();
  _client.initAllObjects();

  return 0;
}