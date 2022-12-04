#include "Configuration.hh"

void Configuration::addLib(char* name) { _libs_names.push_back(name); }

void Configuration::addMobObj(std::string name, Vector3D shift, Vector3D scale,
                              Vector3D rot, Vector3D trans, Vector3D rgb) {
  MobileObj temp;
  temp.SetName(name.c_str());
  temp.SetPosition_m(shift);
  temp.SetRGB(rgb);
  temp.SetTrans(trans);
  temp.SetScale(scale);
  temp.SetRotation(rot);
  std::map<std::string, MobileObj> mapa;

  mapa.insert(std::make_pair(temp.GetName(), temp));
  _scene.addMobileObj(temp);
}

std::vector<std::string> Configuration::getLibNames() { return _libs_names; }
