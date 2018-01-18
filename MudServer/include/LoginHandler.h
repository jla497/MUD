#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <exception>

#include "ConnectionContainer.h"
#include "Handler.h"
#include "PlayHandler.h"

class LoginHandler: public Handler {
    typedef std::vector<std::string> Commands;

    Commands m_commands;
    bool waitingForName;
    std::string outBuffer;
public:
    LoginHandler();
    std::string getBuffer();
    void handle(ConnectionContainer* container, std::string& str);
    std::string getOutBuffer();
    void welcome(ConnectionContainer* container);
    void exit(ConnectionContainer* container);
};

#endif