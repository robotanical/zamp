#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Executor.hh"
#include "Client.hh"
// #include "Scene.hh"
#include <memory>
// #include "MobileObj.hh"

using namespace std;
bool ChangeState(shared_ptr<Scene> Scn) //GeomObject *pObj, AccessControl  *pAccCtrl)
{
  bool Changed;

  while (true) {
    Scn->LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                            // modyfikacje na obiekcie.
    for (MobileObj &rObj : Scn->_Container4Objects) {
       if (!(Changed = rObj.IncStateIndex())) { Scn->UnlockAccess();  return false; }
    }
    Scn->MarkChange();
    Scn->UnlockAccess();
    usleep(300000);
  }
  return true;
}

int main()
{
  Executor executor;
  shared_ptr<Scene> scene;
  scene = make_shared<Scene>();
  executor.initialize("opis_dzialan.cmd");
  executor.configure("config/config.xml");
  Client client;
  client.openConnection();
  client.startCientSender(scene);
  thread Thread4Sending(&Client::communicationThread, &client);
  const char *sConfigCmds =
"Clear\n"
"AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
"AddObj Name=Podstawa1.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
"AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"       
"AddObj Name=Podstawa2 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
"AddObj Name=Podstawa2.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
"AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";


  cout << "Konfiguracja:" << endl;
  cout << sConfigCmds << endl;
  client.send(sConfigCmds);
  cout << "Akcja:" << endl;    
  for (MobileObj &rObj : scene->_Container4Objects) {
    usleep(20000);
    ChangeState(scene);
    scene->MarkChange();
    usleep(100000);
  }
  usleep(100000);
cout << "Close\n" << endl; // To tylko, aby pokazac wysylana instrukcje
  client.send("Close\n");
  client.cancelContinueLooping();
  Thread4Sending.join();
  return 0;
}
