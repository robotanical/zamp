#include "Set4LibInterfaces.hh"

int Set4LibInterfaces::initialize()
{
    std::shared_ptr<LibInterface> move = std::make_shared<LibInterface>();
    move->initialize("libs/libInterp4Move.so");
    _libs.insert(std::make_pair("Move", move));

    std::shared_ptr<LibInterface> set = std::make_shared<LibInterface>();
    set->initialize("libs/libInterp4Set.so");
    _libs.insert(std::make_pair("Set", set));

    std::shared_ptr<LibInterface> pause = std::make_shared<LibInterface>();
    pause->initialize("libs/libInterp4Pause.so");
    _libs.insert(std::make_pair("Pause", pause));

    std::shared_ptr<LibInterface> rotate = std::make_shared<LibInterface>();
    rotate->initialize("libs/libInterp4Rotate.so"); 
    _libs.insert(std::make_pair("Rotate", rotate));

    return 0;
}

Interp4Command * Set4LibInterfaces::getCommand(std::string keyword)
{
    std::shared_ptr<LibInterface> handler;

    
    std::map<std::string, std::shared_ptr<LibInterface>>::iterator iterator = _libs.find(keyword);
    if (iterator == _libs.end())
    {
        std::cout << "Brak wtyczki : " << keyword << std::endl;
        return NULL;
    }
    handler = iterator->second;
    return handler->CreateCmd();
}