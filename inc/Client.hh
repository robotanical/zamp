#pragma once
#include "Port.hh"
#include "AccessControl.hh"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "Scene.hh"

#ifndef CLIENT_HH
#define CLIENT_HH
#define STATES_NUMBER   8

class Client
{
  public:
    Client();
    ~Client();
    bool openConnection();
    void startCientSender(std::shared_ptr<Scene> scene);
    void communicationThread();
    int getContinueLooping();
    void cancelContinueLooping();

    int send( const char *sMesg);
  private:
    bool _continueLooping;
    int _socket;
    std::shared_ptr<Scene> _scene;



};
#endif
