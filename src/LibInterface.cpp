#include "LibInterface.hh"

LibInterface::~LibInterface()
{
    dlclose(_LibHandler);
}

int LibInterface::initialize(std::string libName)
{
    _LibHandler = dlopen(libName.c_str(), RTLD_LAZY);
    void *function;
    const char *(*getCmdName)(void);

    if(!_LibHandler)
    {
        std::cerr << " Brak biblioteki "<< libName << std::endl;
        return 1;
    }

    function = dlsym(_LibHandler, "CreateCmd");

    if(!function)
    {
        std::cerr << "Brak funkcji CreateCmd w bibliotece " << libName <<std::endl;
        return 1;
    }

    this->_pCreateCmd = *reinterpret_cast<Interp4Command*(**)(void)>(&function);
    function = dlsym(_LibHandler, "GetCmdName");

    if(!function)
    {
        std::cerr << "Brak funkcji GetCmdName w bibliotece" <<libName <<std::endl;
        return 1;
    }
    getCmdName = reinterpret_cast<const char*(*)(void)>(function);
    _CmdName = getCmdName();
    return 0;
}

Interp4Command *LibInterface::CreateCmd()
{
    return _pCreateCmd();
}