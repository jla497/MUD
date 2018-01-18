#ifndef HANDLER_H
#define HANDLER_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <exception>

#include "ConnectionContainer.h"

struct find_command {
private:
    std::string str;
public:
find_command(std::string str): str(str) {}
bool operator()(std::string command) const {return command == str;}

};

class ConnectionContainer;

class Handler {
public:
    virtual void handle(ConnectionContainer* container, std::string& str) = 0;
    virtual std::string getOutBuffer() = 0;
    virtual void welcome(ConnectionContainer* container) = 0;
    virtual void exit(ConnectionContainer* container) = 0;
};

#endif