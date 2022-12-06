#include "Set4LibInterfaces.hh"

int Set4LibInterfaces::initialize() {
  std::shared_ptr<LibInterface> move = std::make_shared<LibInterface>();
  move->initialize("libs/libInterp4Move.so");
  _libs.insert(std::make_pair("Move", move));

  std::shared_ptr<LibInterface> set = std::make_shared<LibInterface>();
  set->initialize("libs/libInterp4Set.so");
  _libs.insert(std::make_pair("Set", set));

  std::shared_ptr<LibInterface> pause = std::make_shared<LibInterface>();
  pause->initialize("libs/libInterp4Pause.so");
  _libs.insert(std::make_pair("Pause", pause));

  std::shared_ptr<LibInterface> rotate = std::make_shared<LibInterface>();
  rotate->initialize("libs/libInterp4Rotate.so");
  _libs.insert(std::make_pair("Rotate", rotate));

  return 0;
}

Interp4Command *Set4LibInterfaces::getCommand(std::string keyword) {
  std::shared_ptr<LibInterface> handler;
  if (keyword == "begin_parallel") {
    std::cout << "parallel true" << std::endl;
  } else if (keyword == "end_parallel") {
    std::cout << "parallel false" << std::endl;
  }

  std::map<std::string, std::shared_ptr<LibInterface>>::iterator iterator =
      _libs.find(keyword);
  if (iterator == _libs.end()) {
    std::cout << "Brak wtyczki : " << keyword << std::endl;
    return NULL;
  }
  handler = iterator->second;
  return handler->CreateCmd();
}
int Set4LibInterfaces::initialize(std::vector<std::string> lib_names) {
  for (std::string &name : lib_names) {
    std::shared_ptr<LibInterface> tmp = std::make_shared<LibInterface>();
    std::string cmd_name = "libs/" + name;
    tmp->initialize("libs/" + name);
    std::string name_for_map = cmd_name.substr(0, cmd_name.length() - 3);
    name_for_map = name_for_map.substr(15, name_for_map.length() - 1);
    // std::cout <<name_for_map << std::endl;
    _libs.insert(std::make_pair(name_for_map, tmp));
  }
  return 0;
}