#ifndef CONNECTION_CONTAINER_H
#define CONNECTION_CONTAINER_H

#include <exception>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>

#include "MudProtocol.h"
#include "Protocol.h"
#include "Server.h"

namespace mudserver {
namespace connection {

constexpr unsigned int DEFAULT_NUM_OF_MUD_PROTOCOLS = 512;

class ConnectionContainer {
    networking::Connection mConnection;
    bool isConnected = false;
    MudProtocol mProtocol{DEFAULT_NUM_OF_MUD_PROTOCOLS};

  public:
    ConnectionContainer() = default;
    ConnectionContainer(const networking::Connection &c);

    bool getIsConnected() const;

    // receives messages from ConnectionManager
    void receiveFromServer(std::string &str);

    std::string sendToGameManager();

    void receiveFromGameManager(const std::string &str);

    std::string sendToServer();

    networking::Connection getConnection() const;

  private:
};
} // namespace connection
} // namespace mudserver

#endif
