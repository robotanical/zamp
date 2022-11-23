#ifndef PARSER_HH
#define PARSER_HH
#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include "xmlinterp.hh"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <list>
#include "Configuration.hh"

using namespace std;
using namespace xercesc;

#define LINE_SIZE 500

class Parser
{
    private:
        std::string _cmdFileName;
    public:
        Parser(){};
        int initialize(std::string cmdFileName);
        bool execPreprocessor(std::istringstream &IStrm4Cmds);
        bool ReadFile(const char* sFileName, shared_ptr<Configuration> rConfig);
};
#endif