#include "ConnectionManager.h"
/*checks each ConnectionContainers's isConnected state. If isConnected is false, then remove the container and 
drop connection.*/
void ConnectionManager::dropConnection(Server& server) {
    for(auto& c : m_list) {

        if((*c).getIsConnected() == false) {
            Connection toBeRmved = (*c).getConnection();
            m_list.erase(std::remove(m_list.begin(), m_list.end(),c));
            server.disconnect(toBeRmved);
        }   
    }
}

void ConnectionManager::addConnection(Connection c) {
    auto ptr = std::unique_ptr<ConnectionContainer>(new ConnectionContainer(c));
    m_list.push_back(std::move(ptr));
}

/*pass clients messages to existing connection containers If client does not exist, 
create new connection containers.
*/
void ConnectionManager::passMessages(const std::deque<Message> &incoming) {
    for(auto& msg: incoming) {
        auto conn = msg.connection;
        auto text = msg.text;
        std::cout<<"msg from: "<<msg.connection.id<<" "<<msg.text<<std::endl;

        auto connContainer = std::find_if(m_list.begin(),m_list.end(),find_container(conn));

        if (connContainer == m_list.end()) {
            ConnectionManager::addConnection(conn);
        }

        connContainer = std::find_if(m_list.begin(), m_list.end(),find_container(conn));

        (*connContainer)->receive(text);
    }
}
/*Polls the list of connection containers for any buffered messages waiting to be sent
*/
void ConnectionManager::sendMessages(Server& server) {
    std::deque<Message> messages;

    for(auto& container : m_list) {
        Connection conn = container->getConnection();
        std::string toSend = container->getOutBuffer();
        
        if(!toSend.empty()) {
            Message m_msg = Message{conn,toSend};
            messages.push_back(m_msg);
        }
    }

    server.send(messages);
}

void ConnectionManager::broadCast(Server& server, std::string& broadcast) {
    std::deque<Message> messages;

    for(auto& container : m_list) {
        Connection conn = container->getConnection();
        Message m_msg = Message{conn,broadcast};
        messages.push_back(m_msg);
    }

    server.send(messages);
}

