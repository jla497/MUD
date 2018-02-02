#include "connectionmanager/ConnectionContainer.h"

namespace mudserver {
namespace connection {

ConnectionContainer::ConnectionContainer(): mProtocol(std::unique_ptr<MudProtocol>(new MudProtocol(512))) {}

ConnectionContainer::ConnectionContainer(const networking::Connection& c): mConnection(c), isConnected(true),mProtocol(std::unique_ptr<MudProtocol>(new MudProtocol(512))) {}

ConnectionContainer::ConnectionContainer(ConnectionContainer &&container): mConnection(container.mConnection), mProtocol(std::move(container.mProtocol)) {}

//receives messages from Server -> ConnectionManager->ConnectionContainer->Protocol
void ConnectionContainer::receiveFromServer(std::string& str) {
  // translated = mProtocol.receive(str);
  try {
    mProtocol->receive(str);
  } catch (std::exception& e) {
    //kick user out
    isConnected = false;
    return;
  }

  return;
}

// send to GameManager
std::string ConnectionContainer::sendToGameManager() {
  auto str = mProtocol->send(); 
  return str;
}

void ConnectionContainer::receiveFromGameManager(std::string& str) {
  // std::cout<<"connection container received from game manager: "<<str<<std::endl;
  
  // translated = mProtocol.receive(str);
  try {
   mProtocol->receive(str);
  } catch (std::exception& e) {
    //kick user out
    // std::cout << e.what() << std::endl;
    isConnected = false;
    return;
  }
    return;
}

std::string ConnectionContainer::sendToServer() {
  return mProtocol->send();
}

bool ConnectionContainer::getIsConnected() const {
  return isConnected;
}

networking::Connection ConnectionContainer::getConnection() const {
  return mConnection;
}
}
}