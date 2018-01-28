#include "ConnectionManager.h"

using namespace connection;

ConnectionManager::ConnectionManager(): mList() {}

/*checks each ConnectionContainers's isConnected state. If isConnected is false, then remove the container and
drop connection.*/
void ConnectionManager::dropConnections() {
    for (const auto& c : mList) {

        if ((*c).getIsConnected() == false) {
            const auto& toBeRmved = (*c).getConnection();
            mList.erase(std::remove(mList.begin(), mList.end(), c));
            server.disconnect(toBeRmved);
        }
    }
}

void ConnectionManager::addConnection(networking::Connection c) {
    auto ptr = std::make_unique<ConnectionContainer>(c);

    mList.push_back(std::move(ptr));
}

/*pass clients messages to existing connection containers If client does not exist,
create new connection containers.
*/
void ConnectionManager::rxFromServer(std::deque<networking::Message> &incoming) {
    for (auto& msg : incoming) {
        auto conn = msg.connection;
        auto text = msg.text;
        // std::cout << "msg from: " << msg.connection.id << " " << msg.text << std::endl;

        auto connContainerItr = std::find_if(mList.begin(), mList.end(), findContainer(conn));

        if (connContainerItr == mList.end()) {
            addConnection(conn);
        }

        connContainerItr = std::find_if(mList.begin(), mList.end(), findContainer(conn));
    
        (*connContainerItr)->receiveFromServer(text);
    }
}
/*Polls the list of connection containers for any buffered messages waiting to be sent
*/
std::deque<networking::Message> ConnectionManager::sendToServer() {
    std::deque<networking::Message> messages;

    for (const auto& container : mList) {
        const auto& conn = container->getConnection();
        const auto& toSend = container->sendToServer();

        if (!toSend.empty()) {
            networking::Message m_msg = networking::Message{conn, toSend};
            messages.push_back(m_msg);
        }
    }

    server.send(messages);

    return messages;
}

//collect and pass msgs from protocols to the GameManager
std::unique_ptr<gameAndUserMsgs> ConnectionManager::sendToGameManager() {
    auto msgsToGameManager = std::make_unique<gameAndUserMsgs>();

    for (const auto& container : mList) {
        const auto& user_msg = container->sendToGameManager();
        const auto& c = container->getConnection();
        std::cout<<c.id<<": "<<user_msg<<std::endl;

        if (!user_msg.empty()) {
            auto msg = std::make_unique<gameAndUserInterface>();
            msg->text = user_msg;
            msg->conn = c;
            msgsToGameManager->push_back(std::move(msg));
        }
    }

    return std::move(msgsToGameManager);
}

void ConnectionManager::receiveFromGameManager(std::unique_ptr<gameAndUserMsgs> fromGame) {

    for (auto& msg : *fromGame) {
       auto& connection = msg->conn;
       auto& text = msg->text;
       auto connContainerItr = std::find_if(mList.begin(), mList.end(), findContainer(connection));
       
        if (connContainerItr == mList.end()) {
            auto errMsg = "ConnectionContainer not found while trying to send msg from the GameManager\n";
            throw std::runtime_error(errMsg);
        }

        (*connContainerItr)->receiveFromGameManager(text);
    }
}

//receive msgs to send from GameManager
// void rxFromGameManager(std::vector<Interface2Game> msgs);
