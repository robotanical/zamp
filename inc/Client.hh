#ifndef CLIENT_HH
#define CLIENT_HH
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "AccessControl.hh"
#include "MobileObj.hh"
#include "Port.hh"
#include "Scene.hh"

class Client {
 public:
  Client(Scene& scene) : _scene(scene) { _continueLooping = true; };
  ~Client() { close(_socket); };
  bool openConnection() {
    struct sockaddr_in DaneAdSerw;

    bzero((char*)&DaneAdSerw, sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);

    _socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_socket < 0) {
      std::cerr << "*** Blad otwarcia gniazda." << std::endl;
      return false;
    }

    if (connect(_socket, (struct sockaddr*)&DaneAdSerw, sizeof(DaneAdSerw)) <
        0) {
      std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT
                << std::endl;
      return false;
    }
    std::cout << "Otwarto gniazdo" << std::endl;
    return true;
  };
  void communicationThread() {
    _scene.UnlockAccess();
    while (getContinueLooping()) {
      if (!_scene.IsChanged()) {
        usleep(10000);
        continue;
      }
      _scene.LockAccess();

      for (auto& iterator : _scene.map_mob_objs) {
        send(iterator.second.GetUpdateObj());
      }

      _scene.CancelChange();
      _scene.UnlockAccess();
    }
  };
  void initAllObjects() {
    std::string clr = "Clear\n";
    send(clr);
    for (auto& x : _scene.map_mob_objs) {
      const char* msg = x.second.GetAddObj().c_str();
      send(x.second.GetAddObj());
    }
  };
  int getContinueLooping() { return _continueLooping; };
  void cancelContinueLooping() { _continueLooping = false; };

  int send(std::string stringMesg) {
    const char* sMesg = stringMesg.c_str();
    ssize_t IlWyslanych;
    ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);

    while ((IlWyslanych = write(_socket, sMesg, IlDoWyslania)) > 0) {
      IlDoWyslania -= IlWyslanych;
      sMesg += IlWyslanych;
    }
    if (IlWyslanych < 0) {
      std::cerr << "*** Blad przeslania napisu." << std::endl;
    }
    return 0;
  };

 private:
  bool _continueLooping;
  int _socket;
  Scene& _scene;
};

#endif
