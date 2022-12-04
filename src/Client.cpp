#include "Client.hh"

Client::Client(Scene &scene) : _scene(scene) { _continueLooping = true; }
// ~Client();
bool Client::openConnection() {
  struct sockaddr_in DaneAdSerw;

  bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);

  _socket = socket(AF_INET, SOCK_STREAM, 0);

  if (_socket < 0) {
    std::cerr << "*** Blad otwarcia gniazda." << std::endl;
    return false;
  }

  if (connect(_socket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) <
      0) {
    std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT
              << std::endl;
    return false;
  }
  return true;
}
void Client::communicationThread() {
  //   while (this->getContinueLooping()) {
  //     if (!_scene.IsChanged()) {
  //       usleep(10000);
  //       continue;
  //     }
  //     _scene.LockAccess();

  //------- Przeglądanie tej kolekcji to uproszczony przykład

  //    for (const MobileObj &rObj : _scene._Container4Objects) {
  //                                  // Ta instrukcja to tylko uproszczony
  //                                  przykład
  //  std::cout << rObj.GetStateDesc();
  //      send(rObj.GetStateDesc()); // Tu musi zostać wywołanie odpowiedniej
  //                                        // metody/funkcji gerującej
  //                                        polecenia dla serwera.
  //    }

  //   _scene.CancelChange();
  //   _scene.UnlockAccess();
  // }
}
int Client::getContinueLooping() { return _continueLooping; }
void Client::cancelContinueLooping() { _continueLooping = false; }

int Client::send(const char *sMesg) {
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
}
Client::~Client() { close(_socket); }

void Client::initAllObjects() {
  for (auto const &x : _scene.map_mob_objs) {
    send(x.second.GetAddObj());
  }
}