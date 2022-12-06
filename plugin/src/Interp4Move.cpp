#include "Interp4Move.hh"

#include <iostream>

#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C" {
Interp4Command* CreateCmd(void);
const char* GetCmdName() { return "Move"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void) { return Interp4Move::CreateCmd(); }

/*!
 *
 */
Interp4Move::Interp4Move() : _Speed_mmS(0), _Name(""), _Length_mm(0) {}

/*!
 *
 */
void Interp4Move::PrintCmd() const {
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  std::cout << GetCmdName() << " " << _Name << " " << _Speed_mmS << " "
            << _Length_mm << endl;
}

/*!
 *
 */
const char* Interp4Move::GetCmdName() const { return ::GetCmdName(); }

/*!
 *
 */
bool Interp4Move::ExecCmd(Scene& scene) const {
  Vector3D pos;
  Vector3D rot;
  Vector3D tmp;
  Vector3D new_pos;
  tmp[0] = 0;
  tmp[1] = 0;
  tmp[2] = 0;
  pos = scene.getMobileObj(_Name).GetPosition_m();
  rot[0] = scene.getMobileObj(_Name).GetAng_Roll_deg();
  rot[1] = scene.getMobileObj(_Name).GetAng_Pitch_deg();
  rot[2] = scene.getMobileObj(_Name).GetAng_Yaw_deg();
  double duration = _Length_mm / _Speed_mmS;
  double steps = (int)(duration * 100);
  double step_time = duration / steps;
  double step_length = _Length_mm / steps;
  for (int i = 0; i < steps; i++)

  {
    tmp[0] += step_length * cos(rot[1] * M_PI / 180) * cos(rot[2] * M_PI / 180);
    tmp[1] +=
        step_length * (cos(rot[0] * M_PI / 180) * sin(rot[2] * M_PI / 180) +
                       cos(rot[2] * M_PI / 180) * sin(rot[1] * M_PI / 180) *
                           sin(rot[0] * M_PI / 180));
    tmp[2] +=
        step_length * (sin(rot[0] * M_PI / 180) * sin(rot[2] * M_PI / 180) -
                       cos(rot[0] * M_PI / 180) * cos(rot[2] * M_PI / 180) *
                           sin(rot[1] * M_PI / 180));
    new_pos[0] = tmp[0] + pos[0];
    new_pos[1] = tmp[1] + pos[1];
    new_pos[2] = tmp[2] + pos[2];
    scene.LockAccess();
    scene.getMobileObj(_Name).SetPosition_m(new_pos);
    scene.MarkChange();
    scene.UnlockAccess();
    usleep(step_time * 1000000);
  }
  double remaining_length = _Length_mm - (steps * step_length);
  if (remaining_length) {
    tmp[0] +=
        remaining_length * cos(rot[1] * M_PI / 180) * cos(rot[2] * M_PI / 180);
    tmp[1] += remaining_length *
              (cos(rot[0] * M_PI / 180) * sin(rot[2] * M_PI / 180) +
               cos(rot[2] * M_PI / 180) * sin(rot[1] * M_PI / 180) *
                   sin(rot[0] * M_PI / 180));
    tmp[2] += remaining_length *
              (sin(rot[0] * M_PI / 180) * sin(rot[2] * M_PI / 180) -
               cos(rot[0] * M_PI / 180) * cos(rot[2] * M_PI / 180) *
                   sin(rot[1] * M_PI / 180));
    new_pos[0] = tmp[0] + pos[0];
    new_pos[1] = tmp[1] + pos[1];
    new_pos[2] = tmp[2] + pos[2];
    scene.LockAccess();
    scene.getMobileObj(_Name).SetPosition_m(new_pos);
    scene.MarkChange();
    scene.UnlockAccess();
    usleep(step_time * 1000000);
    // client.send(scene.getMobileObj(_Name).GetUpdateObj());
  }
  return true;
}

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList) {
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >> _Name;
  Strm_CmdsList >> _Speed_mmS;
  Strm_CmdsList >> _Length_mm;

  return true;
}

/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd() { return (new Interp4Move()); }

/*!
 *
 */
void Interp4Move::PrintSyntax() const {
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
