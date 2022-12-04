#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH

#include <string>

#include "Vector3D.hh"

class MobileObj {
  int _StateIdx = 0;
  char* _Cmd4StatDesc = nullptr;
  double _Ang_Yaw_deg = 0;
  double _Ang_Pitch_deg = 0;
  double _Ang_Roll_deg = 0;
  Vector3D _Position_m;
  Vector3D _rgb;
  Vector3D _trans;
  Vector3D _scale;
  std::string _Name;

 public:
  MobileObj() = default;
  MobileObj(const MobileObj&) = default;
  double GetAng_Roll_deg() const { return _Ang_Roll_deg; }
  double GetAng_Pitch_deg() const { return _Ang_Pitch_deg; }
  double GetAng_Yaw_deg() const { return _Ang_Yaw_deg; }
  void SetAng_Roll_deg(double Ang_Roll_deg) { _Ang_Roll_deg = Ang_Roll_deg; }
  void SetAng_Pitch_deg(double Ang_Pitch_deg) {
    _Ang_Pitch_deg = Ang_Pitch_deg;
  }
  void SetRotation(Vector3D rot) {
    SetAng_Roll_deg(rot[0]);
    SetAng_Pitch_deg(rot[1]);
    SetAng_Yaw_deg(rot[2]);
  }
  Vector3D GetRGB() { return _rgb; }
  Vector3D GetScale() { return _scale; }
  void SetRGB(Vector3D rgb) { _rgb = rgb; }
  void SetTrans(Vector3D trans) { _trans = trans; }
  void SetScale(Vector3D scale) { _scale = scale; }
  void SetAng_Yaw_deg(double Ang_Yaw_deg) { _Ang_Yaw_deg = Ang_Yaw_deg; }
  const Vector3D& GetPositoin_m() const { return _Position_m; }
  Vector3D& UsePosition_m() { return _Position_m; }
  void SetPosition_m(const Vector3D& rPos_m) { _Position_m = rPos_m; }
  void SetName(const char* sName) { _Name = sName; }
  const std::string& GetName() const { return _Name; }
  void SetCmds(char* CmdsTab) { _Cmd4StatDesc = CmdsTab; }
  const char* GetStateDesc() const { return _Cmd4StatDesc; }
  const char* GetAddObj() const {
    std::string tmp;
    tmp += "AddObj Name=";
    tmp += _Name;
    tmp += " RotXYZ=(";
    tmp += std::to_string(_Ang_Roll_deg) + ",";
    tmp += std::to_string(_Ang_Pitch_deg) + ",";
    tmp += std::to_string(_Ang_Yaw_deg) + ") ";
    tmp += "Scale=(";
    tmp += std::to_string(_scale[0]) + "," + std::to_string(_scale[1]) + "," +
           std::to_string(_scale[2]) + ") ";
    tmp += "Shift=(";
    tmp += std::to_string(_Position_m[0]) + "," +
           std::to_string(_Position_m[1]) + "," +
           std::to_string(_Position_m[2]) + ") ";
    tmp += "RGB=(";
    tmp += std::to_string(_rgb[0]) + "," + std::to_string(_rgb[1]) + "," +
           std::to_string(_rgb[2]) + ") ";
    tmp += "Trans_m=(";
    tmp += std::to_string(_trans[0]) + "," + std::to_string(_trans[1]) + "," +
           std::to_string(_trans[2]) + ") ";
    return tmp.c_str();
  }
};

#endif
