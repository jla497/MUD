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


/*ConnectionContainer is a wrapper for the Connection object, 
handlers for user's current state, and the application protocol
object*/


class ConnectionContainer {
    networking::Connection mConnection;
    bool isConnected;
    std::unique_ptr<Protocol> m_protocol;
    Entity m_entity;
    
    ConnectionContainer(const networking::Connection& c);

    public:
     // temporary fix until I find a better solution
    std::string username; //temporary fix until we have a user db

    ConnectionContainer(const Connection& c);

    //receives messages from ConnectionManager
    void receive(const std::string& str);

    bool getIsConnected();

    //send raw string to application protocol object
    void sendToProtocol(const std::string& str);

    networking::Connection getConnection() const;

    std::string getOutBuffer();
};

#endif