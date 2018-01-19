#ifndef HANDLER_H
#define HANDLER_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <exception>

#include "ConnectionContainer.h"

/*functor for searching handler commands*/
struct find_command {
private:
    std::string str;
public:
find_command(std::string str): str(str) {}
bool operator()(std::string command) const {return command == str;}

};

class ConnectionContainer;

/*interface for user handlers. Possible handlers are login, game play, superuser etc.*/
class Handler {
public:
	//receives input strings from containers that are commands or chats. Interfaces with GameManager
    virtual void handle(ConnectionContainer* container, std::string& str) = 0;
    //method called when handler is first called
    virtual void welcome(ConnectionContainer* container) = 0;
    virtual std::string getUserInput() = 0;
    //method called when handler exits
    virtual void exit(ConnectionContainer* container) = 0;
};

#endif