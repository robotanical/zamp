#include <dlfcn.h>

#include <cassert>
#include <iostream>

#include "Client.hh"
#include "Executor.hh"
// #include "Scene.hh"
#include <memory>
// #include "MobileObj.hh"

using namespace std;
// bool ChangeState(
//     shared_ptr<Scene> Scn)  // GeomObject *pObj, AccessControl  *pAccCtrl)
// {
//   bool Changed;

//   while (true) {
//     Scn->LockAccess();  // Zamykamy dostęp do sceny, gdy wykonujemy
//                         // modyfikacje na obiekcie.
//     for (MobileObj &rObj : Scn->_Container4Objects) {
//       if (!(Changed = rObj.IncStateIndex())) {
//         Scn->UnlockAccess();
//         return false;
//       }
//     }
//     Scn->MarkChange();
//     Scn->UnlockAccess();
//     usleep(300000);
//   }
//   return true;
// }

int main() {
  // Configuration config;
  Scene scene;

  Executor executor(scene);
  // scene = make_shared<Scene>();
  executor.configure("config/config.xml");
  executor.initialize("opis_dzialan.cmd");

  // Client client;
  // client.openConnection();
  // client.startCientSender(scene);
  // thread Thread4Sending(&Client::communicationThread, &client);

  // cout << "Konfiguracja:" << endl;
  // cout << sConfigCmds << endl;
  // client.send(sConfigCmds);
  // cout << "Akcja:" << endl;
  // for (MobileObj &rObj : scene._Container4Objects) {
  //   usleep(20000);
  //   ChangeState(scene);
  //   scene.MarkChange();
  //   usleep(100000);
  // }
  // usleep(100000);
  // cout << "Close\n" << endl;  // To tylko, aby pokazac wysylana instrukcje
  // client.send("Close\n");
  // client.cancelContinueLooping();
  // Thread4Sending.join();
  return 0;
}
