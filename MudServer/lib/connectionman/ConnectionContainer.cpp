#include "ConnectionContainer.h"

ConnectionContainer::ConnectionContainer(const networking::Connection& c): mConnection(c), mProtocol(std::unique_ptr<MudProtocol>(new MudProtocol(512))), isConnected(true) {}

    //fix this to unique_ptrs
    LoginHandler* loginHandle = new LoginHandler();

//receives messages from Server -> ConnectionManager->ConnectionContainer->Protocol
void ConnectionContainer::receiveFromServer(std::string& str) {
  // translated = mProtocol.receive(str);
  try {
    mProtocol->receive(str);
  } catch (std::exception& e) {
    //kick user out
    // std::cout << e.what() << std::endl;
    isConnected = false;
    return;
  }

    username = "";

   
}

<<<<<<< HEAD
=======
void ConnectionContainer::pushToStack(Handler& handler) {
  m_handlers.push(&handler); 
  m_handlers.top()->welcome(this);
}

>>>>>>> daadc40f63c104d98d68f948b73681792c9742b3
void ConnectionContainer::receiveFromGameManager(std::string& str) {
  // std::cout<<"connection container received from game manager: "<<str<<std::endl;
  
  // translated = mProtocol.receive(str);
  try {
   mProtocol->receive(str);
  } catch (std::exception& e) {
    //kick user out
    // std::cout << e.what() << std::endl;
<<<<<<< HEAD

=======
>>>>>>> daadc40f63c104d98d68f948b73681792c9742b3
    isConnected = false;
    return;
  }
  
  return;
}

bool ConnectionContainer::getIsConnected() {
  return isConnected;
}

networking::Connection ConnectionContainer::getConnection() const {
  return mConnection;
}

std::string ConnectionContainer::getOutBuffer() {
  return m_protocol->send();
}

void ConnectionContainer::sendToProtocol(const std::string& str) {
  m_protocol->sendToBuffer(str);
}
