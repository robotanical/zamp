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
  void addMobileObj(MobileObj &obj)
    {
  std::string name = obj.GetName();
  MobileObj nowy = MobileObj(obj);
  map_mob_objs[name.c_str()] = nowy;
  std::cout<< nowy.GetRGB() << std::endl;
};
  MobileObj& getMobileObj(std::string name)
  { return map_mob_objs[name]; };

};

// #endif