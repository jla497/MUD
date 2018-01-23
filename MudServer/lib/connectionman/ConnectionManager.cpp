#include "ConnectionManager.h"

/*checks each ConnectionContainers's isConnected state. If isConnected is false, then remove the container and
drop connection.*/
void ConnectionManager::dropConnections() {
    for (const auto& c : m_list) {

        if ((*c).getIsConnected() == false) {
            const auto& toBeRmved = (*c).getConnection();
            m_list.erase(std::remove(m_list.begin(), m_list.end(), c));
            server.disconnect(toBeRmved);
        }
    }
}

void ConnectionManager::addConnection(Connection c) {
    auto ptr = std::make_unique<ConnectionContainer>(c);
    m_list.push_back(std::move(ptr));
}

/*pass clients messages to existing connection containers If client does not exist,
create new connection containers.
*/
void ConnectionManager::rxFromServer(const std::deque<Message> &incoming) {
    for (const auto& msg : incoming) {
        auto& conn = msg.connection;
        const auto& text = msg.text;
        // std::cout << "msg from: " << msg.connection.id << " " << msg.text << std::endl;

        auto connContainer = std::find_if(m_list.begin(), m_list.end(), find_container(conn));

        if (connContainer == m_list.end()) {
            ConnectionManager::addConnection(conn);
        }

        connContainer = std::find_if(m_list.begin(), m_list.end(), find_container(conn));

        (*connContainer)->receive(text);
    }
}
/*Polls the list of connection containers for any buffered messages waiting to be sent
*/
void ConnectionManager::sendToServer() {
    std::deque<Message> messages;

    for (const auto& container : m_list) {
        const auto& conn = container->getConnection();
        const auto& toSend = container->getOutBuffer();

        if (!toSend.empty()) {
            Message m_msg = Message{conn, toSend};
            messages.push_back(m_msg);
        }
    }

    server.send(messages);
}

//collect and pass msgs from protocols to the GameManager
MsgsPtr ConnectionManager::send2GameManager() {
    auto ptr = std::make_unique<Msgs>();

    for (const auto& container : m_list) {
        const auto& user_msg = container->getHandler().getUserInput();
        const auto& c = container->getConnection();

        if (!user_msg.empty()) {
            auto msg = std::make_unique<Interface2Game>();
            msg->text = user_msg;
            msg->conn = c;
            ptr->push_back(std::move(msg));
        }
    }

    return ptr;
}

//receive msgs to send from GameManager
// void rxFromGameManager(std::vector<Interface2Game> msgs);

void ConnectionManager::run() {
    std::cout << "---------------------MUD Server Console---------------------" << std::endl;

    done = false;
   
    while (!done) {
        try {
            server.update();
        } catch (std::exception& e) {
            printf("Exception from Server update:\n%s\n\n", e.what());
            done = true;
        }

        auto incoming = server.receive();

        rxFromServer(incoming);

        auto msgsPtr = send2GameManager();

        for (const auto& msg : *msgsPtr) {
            std::cout << "GameManager will get msg from: " << msg->conn.id << msg->text << std::endl;
        }

        dropConnections();

        sleep(1);
    }
}

void ConnectionManager::quit() {
    done = true;
}

