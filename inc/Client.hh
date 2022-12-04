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
#include "Port.hh"
#include "Scene.hh"

class Client {
 public:
  Client(Scene& scene);
  ~Client();
  bool openConnection();
  void communicationThread();
  void initAllObjects();
  int getContinueLooping();
  void cancelContinueLooping();

  int send(const char* sMesg);

 private:
  bool _continueLooping;
  int _socket;
  Scene& _scene;
};
#endif
