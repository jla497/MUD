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
}

void ConnectionContainer::pushToStack(Handler& handler) {
  m_handlers.push(&handler); 
  m_handlers.top()->welcome(this);
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

  // std::cout<<randid<<" msg received: "<<translated<<std::endl;

  //pass translated msg to handler
  if(!translated.empty()) {
   m_handlers.top()->handle(this,translated);
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