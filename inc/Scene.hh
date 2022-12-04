// #ifndef SCENE_HH
// #define SCENE HH
#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>

#include "AccessControl.hh"
#include "MobileObj.hh"

class Scene : public AccessControl {
 public:
  std::map<std::string, MobileObj> map_mob_objs;
  void addMobileObj(MobileObj &obj);
  MobileObj getMobileObj(std::string name);
};
// #endif