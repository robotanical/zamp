#include "Scene.hh"

void Scene::addMobileObj(MobileObj &obj) {
  std::string name = obj.GetName();
  MobileObj nowy = MobileObj(obj);
  map_mob_objs[name.c_str()] = nowy;
}

MobileObj Scene::getMobileObj(std::string name) { return map_mob_objs[name]; }