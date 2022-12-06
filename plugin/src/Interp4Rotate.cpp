#include "Interp4Rotate.hh"

#include <iostream>

#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C" {
Interp4Command* CreateCmd(void);
const char* GetCmdName() { return "Rotate"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void) { return Interp4Rotate::CreateCmd(); }

/*!
 *
 */
Interp4Rotate::Interp4Rotate() : _Speed_deg(0), _angle(0), _name("") {}

/*!
 *
 */
void Interp4Rotate::PrintCmd() const {
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _name << " " << _Speed_deg << " " << _angle
       << endl;
}

/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const { return ::GetCmdName(); }

/*!
 *
 */
bool Interp4Rotate::ExecCmd(Scene& scene) const {
  Vector3D rot;
  rot[0] = scene.getMobileObj(_name).GetAng_Roll_deg();
  rot[1] = scene.getMobileObj(_name).GetAng_Pitch_deg();
  rot[2] = scene.getMobileObj(_name).GetAng_Yaw_deg();

  double duration = _angle / _Speed_deg;
  double steps = (int)(duration * 100);
  double step_duration = duration / steps;
  double step_deg = _angle / steps;

  double tmp = 0;
  for (int i = 0; i < steps; ++i) {
    scene.LockAccess();
    tmp += step_deg;
    rot[2] = tmp + rot[2];
    scene.getMobileObj(_name).SetRotation(rot);
    scene.MarkChange();
    scene.UnlockAccess();
    usleep(step_duration * 1000000);
  }
  return true;

  return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList) {
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >> _name;
  Strm_CmdsList >> _Speed_deg;
  Strm_CmdsList >> _angle;
  return true;
}

/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd() { return new Interp4Rotate(); }

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const {
  cout << "   Rotate  NazwaObiektu  Szybkosc[deg/s]  kat obrotu[deg]" << endl;
}
