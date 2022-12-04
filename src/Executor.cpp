#include "Executor.hh"

Executor::Executor(Scene &scene) : _scene(scene) {
  _config = std::make_shared<Configuration>(_scene);
  //   client client(_scene);
}

Executor::~Executor() { delete _command; }

int Executor::initialize(std::string cmdFName) {
  _parser.initialize(cmdFName.c_str());
  _parser.execPreprocessor(_stream);
  // _libs_handler.initialize();

  return 0;
}

int Executor::configure(std::string configFName) {
  _parser.ReadFile(configFName.c_str(), _config);
  std::cout << "cokolwiek" << std::endl;

  _libs_handler.initialize(_config->getLibNames());
  _client.openConnection();
  _client.initAllObjects();
  std::cout << "cokolwiek" << std::endl;

  return 0;
}