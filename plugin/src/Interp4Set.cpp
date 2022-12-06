#include "Interp4Set.hh"

#include <iostream>

#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C" {
Interp4Command* CreateCmd(void);
const char* GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void) { return Interp4Set::CreateCmd(); }

/*!
 *
 */
Interp4Set::Interp4Set() : _name(""), _x(0), _y(0), _angle_OZ(0) {}

/*!
 *
 */
void Interp4Set::PrintCmd() const {
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _x << " " << _y << " " << _angle_OZ << endl;
}

/*!
 *
 */
const char* Interp4Set::GetCmdName() const { return ::GetCmdName(); }

/*!
 *
 */
bool Interp4Set::ExecCmd(Scene& scene) const {
  Vector3D pos;
  pos[0] = _x;
  pos[1] = _y;
  pos[2] = scene.getMobileObj(_name).GetPosition_m()[2];
  Vector3D rot;
  rot[0] = scene.getMobileObj(_name).GetAng_Roll_deg();
  rot[1] = scene.getMobileObj(_name).GetAng_Pitch_deg();
  rot[2] = _angle_OZ;
  scene.LockAccess();
  // scene.getMobileObj(_name).SetPosition_m(pos);
  scene.getMobileObj(_name).SetRotation(rot);
  scene.MarkChange();
  scene.UnlockAccess();
  return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList) {
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >> _name;
  Strm_CmdsList >> _x;
  Strm_CmdsList >> _y;
  Strm_CmdsList >> _angle_OZ;
  return true;
}

/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd() { return new Interp4Set(); }

/*!
 *
 */
void Interp4Set::PrintSyntax() const {
  cout << "   Set  NazwaObiektu  wsp_x    wsp_y     kat_OZ" << endl;
}
