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

using namespace networking;

/*ConnectionContainer is a wrapper for the Connection object,
handlers for user's current state, and the application protocol
object*/
class ConnectionContainer {
    Connection mConnection;
    bool isConnected;
    std::unique_ptr<MudProtocol> mProtocol;

public:
    ConnectionContainer();
    
    ConnectionContainer(const Connection& c);

    ConnectionContainer(ConnectionContainer const &) = delete;
    
    ConnectionContainer &operator= (ConnectionContainer const &) = delete;
  
    ConnectionContainer(ConnectionContainer &&container);

    ConnectionContainer &operator=(ConnectionContainer &&container) {
        if(this != &container) {
            mProtocol = std::move(container.mProtocol);
        }

        return *this;
    } 

    bool getIsConnected() const;

    //receives messages from ConnectionManager
    void receiveFromServer(std::string& str);

    std::string sendToGameManager();

    void receiveFromGameManager(std::string& str);

    std::string sendToServer();
    //send raw string to application protocol object
    void sendToProtocol(const std::string& str);

    Connection getConnection() const;

    std::string getOutBuffer();

    MudProtocol& getProtocol() const;
};

#endif