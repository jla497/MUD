#include "connectionmanager/ConnectionManager.h"

namespace mudserver {
namespace connection {

ConnectionManager::ConnectionManager(networking::Port port)
    : mList(), server{port,
                      [this](networking::Connection c) {
                          printf("New connection found: %lu\n", c.id);
                          this->addConnection(c);
                      },

                      [](networking::Connection c) {
                          printf("Connection lost: %lu\n", c.id);
                      }} {}

/*checks each ConnectionContainers's isConnected state. If isConnected is false,
then remove the container and drop connection.*/
void ConnectionManager::dropConnections() {

    std::remove_if(mList.begin(), mList.end(), [this](auto &c) {
        if (!c.getIsConnected()) {
            server.disconnect(c.getConnection());
            return true;
        }
        return false;
    });
}

void ConnectionManager::addConnection(networking::Connection c) {
    mList.emplace_back(c);
}

/*pass clients messages to existing connection containers If client does not
exist, create new connection containers.
*/
void ConnectionManager::rxFromServer(
    std::deque<networking::Message> &incoming) {
    for (auto &msg : incoming) {
        auto conn = msg.connection;
        auto text = msg.text;

        auto connContainerItr =
            std::find_if(mList.begin(), mList.end(), findContainer(conn));

        if (connContainerItr == mList.end()) {
            addConnection(conn);
        }

        connContainerItr =
            std::find_if(mList.begin(), mList.end(), findContainer(conn));

        connContainerItr->receiveFromServer(text);
    }
}

/*Polls the list of connection containers for any buffered messages waiting to
 * be sent
 */
std::deque<networking::Message> ConnectionManager::sendToServer() {
    std::deque<networking::Message> messages;

    for (auto &container : mList) {
        const auto &conn = container.getConnection();
        const auto &toSend = container.sendToServer();

        if (!toSend.empty()) {
            messages.push_back(networking::Message{conn, toSend});
        }
    }

    server.send(messages);
    return messages;
}

// collect and pass msgs from protocols to the GameManager
std::vector<gameAndUserInterface> ConnectionManager::sendToGameManager() {
    std::vector<gameAndUserInterface> msgsToGameManager;

    for (auto &container : mList) {
        const auto &user_msg = container.sendToGameManager();
        const auto &c = container.getConnection();
        // std::cout<<c.id<<": "<<user_msg<<std::endl;

        if (!user_msg.empty()) {
            msgsToGameManager.push_back({user_msg, c});
        }
    }

    return msgsToGameManager;
}

/*receive from GameManager then send to protcol for translating before going to
 * the server*/
void ConnectionManager::receiveFromGameManager(
    const std::vector<gameAndUserInterface> &fromGame) {

    for (auto &msg : fromGame) {
        auto it =
            std::find_if(mList.begin(), mList.end(), findContainer(msg.conn));
        if (it == mList.end()) {
            auto errMsg = "ConnectionContainer not found while trying to send "
                          "msg from the GameManager\n";
            throw std::runtime_error(errMsg);
        }
        it->receiveFromGameManager(msg.text);
    }
}

bool ConnectionManager::update() {
    try {
        server.update();
    } catch (std::exception &e) {
        printf("Exception from Server update:\n%s\n\n", e.what());
        return true;
    }

    auto incoming = server.receive();
    rxFromServer(incoming);
    // sendToServer();
    dropConnections();

    return false;
}
} // namespace connection
} // namespace mudserver
// receive msgs to send from GameManager
// void rxFromGameManager(std::vector<Interface2Game> msgs);


