#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Parser.hh"
#include "Set4LibInterfaces.hh"
#include "Configuration.hh"

using namespace std;


int main()
{
  Parser parser;
  Set4LibInterfaces libsHandler;
  std::istringstream stream;
  parser.initialize("opis_dzialan.cmd");
  parser.execPreprocessor(stream);
    Configuration rConfig;


  libsHandler.initialize();
  Interp4Command* command;
  std::string keyword;
  parser.ReadFile("config/config.xml", rConfig);
  
  while (stream >> keyword)
    {
      command = libsHandler.getCommand(keyword);
      command->ReadParams(stream);
      std::cout << "Wyswietl polecenie:" << std::endl;
      command->PrintCmd();
    }


  return 0;
}
