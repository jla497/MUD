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

<<<<<<< HEAD
<<<<<<< HEAD
=======
// using namespace networking;

>>>>>>> daadc40f63c104d98d68f948b73681792c9742b3

/*ConnectionContainer is a wrapper for the Connection object, 
handlers for user's current state, and the application protocol
object*/


=======
// using namespace networking;

/*ConnectionContainer is a wrapper for the Connection object,
handlers for user's current state, and the application protocol
object*/
>>>>>>> master
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

<<<<<<< HEAD
=======
        return *this;
    } 

    bool getIsConnected() const;

>>>>>>> master
    //receives messages from ConnectionManager
    void receiveFromServer(std::string& str);

    std::string sendToGameManager();

    void receiveFromGameManager(std::string& str);

    std::string sendToServer();
    //send raw string to application protocol object
    void sendToProtocol(const std::string& str);

    networking::Connection getConnection() const;

    std::string getOutBuffer();

    MudProtocol& getProtocol() const;
};

#endif
