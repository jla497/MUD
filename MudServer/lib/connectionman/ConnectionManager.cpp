#include "ConnectionManager.h"

ConnectionManager::ConnectionManager() {
    m_list = new ConnectionList();
}

/*checks each ConnectionContainers's isConnected state. If isConnected is false, then remove the container and
drop connection.*/
void ConnectionManager::dropConnections() {
    for (const auto& c : *m_list) {

        if ((*c).getIsConnected() == false) {
            const auto& toBeRmved = (*c).getConnection();
            m_list->erase(std::remove(m_list->begin(), m_list->end(), c));
            server.disconnect(toBeRmved);
        }
    }
}

void ConnectionManager::addConnection(Connection c) {
    auto ptr = std::make_unique<ConnectionContainer>(c);

    m_list->push_back(std::move(ptr));
}

/*pass clients messages to existing connection containers If client does not exist,
create new connection containers.
*/
void ConnectionManager::rxFromServer(std::deque<Message> &incoming) {
    for (auto& msg : incoming) {
        auto conn = msg.connection;
        auto text = msg.text;
        // std::cout << "msg from: " << msg.connection.id << " " << msg.text << std::endl;

        auto connContainerItr = std::find_if(m_list->begin(), m_list->end(), find_container(conn));

        if (connContainerItr == m_list->end()) {
            addConnection(conn);
        }

        connContainerItr = std::find_if(m_list->begin(), m_list->end(), find_container(conn));
    
        (*connContainerItr)->receiveFromServer(text);
    }
}
/*Polls the list of connection containers for any buffered messages waiting to be sent
*/
std::deque<Message> ConnectionManager::sendToServer() {
    std::deque<Message> messages;

    for (const auto& container : *m_list) {
        const auto& conn = container->getConnection();
        const auto& toSend = container->sendToServer();

        if (!toSend.empty()) {
            Message m_msg = Message{conn, toSend};
            messages.push_back(m_msg);
        }
    }

    server.send(messages);

    return messages;
}

//collect and pass msgs from protocols to the GameManager
gameAndUserMsgs& ConnectionManager::send2GameManager() {
    
    for (const auto& container : *m_list) {
        const auto& user_msg = container->sendToGameManager();
        const auto& c = container->getConnection();
        std::cout<<c.id<<": "<<user_msg<<std::endl;

        if (!user_msg.empty()) {
            auto msg = std::make_unique<gameAndUserInterface>();
            msg->text = user_msg;
            msg->conn = c;
            msgsToGameManager.push_back(std::move(msg));
        }
    }

    return msgsToGameManager;
}

void ConnectionManager::receiveFromGameManager(gameAndUserMsgs& fromGame) {
    msgsToGameManager.clear();
    msgsToGameManager.swap(fromGame);

    std::cout<<"in receiveFromGameManager"<<std::endl;
    for(auto& container : *m_list) {
        const auto& c = container->getConnection();
        std::cout<<"current container in m_list: "<<c.id<<std::endl;
    }

    for (auto& msg : msgsToGameManager) {
       auto& connection = msg->conn;
       auto& text = msg->text;
       auto connContainerItr = std::find_if(m_list->begin(), m_list->end(), find_container(connection));
       
        if (connContainerItr == m_list->end()) {
            auto errMsg = "ConnectionContainer not found while trying to send msg from the GameManager\n";
            throw std::runtime_error(errMsg);
        }

        (*connContainerItr)->receiveFromGameManager(text);
    }
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

        // auto msgsPtr = send2GameManager();

        // for (const auto& msg : *msgsPtr) {
        //     std::cout << "GameManager will get msg from: " << msg->conn.id << msg->text << std::endl;
        // }

        dropConnections();

        sleep(1);
    }
}

void ConnectionManager::quit() {
    done = true;
}

