#ifndef PLAY_HANDLER_H
#define PLAY_HANDLER_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <exception>

#include "ConnectionContainer.h"
#include "Handler.h"

class PlayHandler: public Handler {
    typedef std::vector<std::string> Commands;

    Commands m_commands;
    std::string outBuffer;
public:
    PlayHandler();
    void handle(ConnectionContainer* container, std::string& str);
    std::string getOutBuffer();
    void welcome(ConnectionContainer* container);
    void exit(ConnectionContainer* container);
};

#endif