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


/*ConnectionContainer is a wrapper for the Connection object, 
handlers for user's current state, and the application protocol
object*/
class ConnectionContainer {
    Connection m_connection;
    bool isConnected;
    unique_ptr<Protocol> m_protocol;
    
    int randid;
    std::string outBuffer;
    std::stack<Handler*> m_handlers;

    public:
     // temporary fix until I find a better solution
    std::string username; //temporary fix until we have a user db

    ConnectionContainer(const Connection& c);

    //push a new user state handler onto stack
    void pushToStack(Handler* handler);

    //receives messages from ConnectionManager
    void receive(std::string& str);

    bool getIsConnected();

    //send raw string to application protocol object
    void sendToProtocol(std::string& str);

    Connection getConnection();

    std::string getOutBuffer();
};

#endif