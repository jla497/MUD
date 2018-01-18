#ifndef CONNECTION_CONTAINER_H
#define CONNECTION_CONTAINER_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <exception>
#include <stack>

#include "Protocol.h"
#include "MudProtocol.h"
#include "Server.h"
#include "Handler.h"
#include "LoginHandler.h"

using namespace networking; 

class ConnectionContainer {
    Connection m_connection;
    bool isConnected;
    
    int randid;
    std::string outBuffer;
    std::stack<Handler*> m_handlers;

    public:
    Protocol* m_protocol; // temporary fix until I find a better solution
    std::string username; //temporary fix until we have a user db

    ConnectionContainer(const Connection& c);

    void pushToStack(Handler* handler);

    //receives messages from ConnectionManager
    void receive(std::string& str);

    bool getIsConnected();

    Connection getConnection();

    std::string getOutBuffer();
};

#endif