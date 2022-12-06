#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Interp4Command.hh"
#include "LibInterface.hh"

class Set4LibInterfaces {
 private:
  std::map<std::string, std::shared_ptr<LibInterface>> _libs;
  bool is_parallel = false;

 public:
  int initialize();
  int initialize(std::vector<std::string> lib_names);
  Interp4Command* getCommand(std::string keyword);
  bool isParallel();
};