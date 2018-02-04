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
class ConnectionContainer {
    networking::Connection mConnection;
    bool isConnected;
    std::unique_ptr<MudProtocol> mProtocol;

public:
    ConnectionContainer();

    ConnectionContainer(const networking::Connection &c);

    ConnectionContainer(ConnectionContainer const &) = delete;

    ConnectionContainer &operator=(ConnectionContainer const &) = delete;

    ConnectionContainer(ConnectionContainer &&container);

    ConnectionContainer &operator=(ConnectionContainer &&container) {
        if (this != &container) {
            mProtocol = std::move(container.mProtocol);
        }
        return *this;
    }

    bool getIsConnected() const;

    // receives messages from ConnectionManager
    void receiveFromServer(std::string &str);

    std::string sendToGameManager();

    void receiveFromGameManager(std::string &str);

    std::string sendToServer();

    networking::Connection getConnection() const;

private:
    static const int DEFAULT_NUM_OF_MUD_PROTOCOLS;
};
}  // namespace connection
}  // namespace mudserver

#endif