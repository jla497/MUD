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

class ConnectionContainer {
    networking::Connection mConnection;
    bool isConnected;
    std::unique_ptr<MudProtocol> mProtocol;

public:
    ConnectionContainer();
    
    ConnectionContainer(const networking::Connection& c);

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
    
    networking::Connection getConnection() const;

};

#endif
