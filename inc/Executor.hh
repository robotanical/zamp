#ifndef EXECUTOR_HH
#define EXECUTOR_HH
#include <dlfcn.h>

#include <cassert>
#include <iostream>
#include <string>

#include "Client.hh"
#include "Configuration.hh"
#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "MobileObj.hh"
#include "Parser.hh"
#include "Scene.hh"
#include "Set4LibInterfaces.hh"

class Executor {
 public:
  Executor(Scene& scene);
  ~Executor();
  int initialize(std::string cmdFName);
  int configure(std::string configFName);

 private:
  Parser _parser;
  Set4LibInterfaces _libs_handler;
  std::shared_ptr<Configuration> _config;
  Interp4Command* _command;
  std::istringstream _stream;
  Scene& _scene;
  std::string keyword;
  Client _client = Client(_scene);
  std::thread* sending_thread;
};
#endif