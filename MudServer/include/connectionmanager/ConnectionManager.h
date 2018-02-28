#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <sstream>

#include <unistd.h>

#include "ConnectionContainer.h"
#include "Protocol.h"
#include "Server.h"
#include <memory>
#include <string>

namespace mudserver {
namespace connection {

struct gameAndUserInterface {
    std::string text;
    networking::Connection conn;
};

/*functor used in searches*/
struct findGameAndUserInterface {
    findGameAndUserInterface(networking::Connection conn) : conn(conn) {}

    bool operator()(const gameAndUserInterface &conn) const {
        return this->conn.id == conn.conn.id;
    }

  private:
    networking::Connection conn;
};

struct findContainer {
    findContainer(networking::Connection conn) : conn(conn) {}

    bool operator()(const ConnectionContainer conn) const {
        return this->conn.id == conn.getConnection().id;
    }

  private:
    networking::Connection conn;
};

/*Connection Manager manages ConnectionContainers.
 Adds new connections and removes connections.
 Passes on or broadcasts incoming and outgoing messages*/
class ConnectionManager {
    // auto onConnect = [this](Connection c) {
    // 	printf("New connection found: %lu\n", c.id);
    // 	this->addConnection(c);
    // };

    // auto onDisconnect = [this](Connection c) {
    // 	printf("Connection lost: %lu\n", c.id);
    // };

    std::vector<ConnectionContainer> mList;
    networking::Server server;

  public:
    ConnectionManager(networking::Port port);
    // pass signals to server to drop connections
    void dropConnections();

    void addConnection(const networking::Connection c);

    // pass incoming Messages from server to connection containers
    void rxFromServer(std::deque<networking::Message> &incoming);

    // send Messages to server
    std::deque<networking::Message> sendToServer();

    // collect and pass msgs from protocols to the GameManager
    std::vector<gameAndUserInterface> sendToGameManager();

    // collect and pass msgs from GameManager to ConnectionManager
    void
    receiveFromGameManager(const std::vector<gameAndUserInterface> &fromGame);

    bool update();
};

} // end of namespace connection
} // namespace mudserver
#endif
