#include "Executor.hh"

Executor::Executor(Scene &scene) : _scene(scene) {
  _config = std::make_shared<Configuration>(_scene);
  //   client client(_scene);
}

Executor::~Executor() {
  delete _command;
  for (int i = 0; i < parallel_actions.size(); i++) {
    if (parallel_actions[i].joinable()) parallel_actions[i].join();
  }
}

int Executor::initialize(std::string cmdFName) {
  std::string key;
  _parser.initialize(cmdFName.c_str());
  _parser.execPreprocessor(_stream);
  while (_stream >> key) {
    _command = _libs_handler.getCommand(key);
    if (_command != nullptr) {
      _command->ReadParams(_stream);
      if (_libs_handler.isParallel()) {
        parallel_actions.push_back(
            std::thread(&Interp4Command::ExecCmd, _command, std::ref(_scene)));
      } else {
        for (int i = 0; i < parallel_actions.size(); i++) {
          if (parallel_actions[i].joinable()) parallel_actions[i].join();
        }
        _command->ExecCmd(_scene);
      }
      // _command->ExecCmd(_scene);
    }
  }
  return 0;
}

int Executor::configure(std::string configFName) {
  _parser.ReadFile(configFName.c_str(), _config);
  _libs_handler.initialize(_config->getLibNames());
  _client.openConnection();
  _client.initAllObjects();
  sending_thread = new std::thread(&Client::communicationThread, &_client);

  return 0;
}