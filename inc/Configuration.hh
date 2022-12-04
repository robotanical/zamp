#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH
#include <Scene.hh>
#include <memory>
#include <string>
#include <vector>

#include "Vector3D.hh"

class Configuration {
 public:
  Configuration(Scene& scene) : _scene(scene){};
  // void initialize(Scene& scene);
  void addLib(char* name);
  void addMobObj(std::string name, Vector3D shift, Vector3D scale, Vector3D rot,
                 Vector3D trans, Vector3D rgb);
  std::vector<std::string> getLibNames();

 private:
  std::vector<std::string> _libs_names;
  Scene& _scene;
};

#endif
