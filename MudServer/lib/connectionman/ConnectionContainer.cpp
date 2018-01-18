#include "ConnectionContainer.h"

ConnectionContainer::ConnectionContainer(const Connection& c) {
    m_connection = c;
    
    m_protocol = new MudProtocol(512);
    
    isConnected = true;
    
    randid = rand();

    //fix this to unique_ptrs
    LoginHandler* loginHandle = new LoginHandler();

    this->pushToStack(loginHandle);

   
}

void ConnectionContainer::pushToStack(Handler* handler) {
  m_handlers.push(handler); 
  m_handlers.top()->welcome(this);
}

//receives messages from ConnectionManager
void ConnectionContainer::receive(std::string& str) {
  std::string translated;

  // translated = m_protocol.receive(str);
  try{
    translated = m_protocol->receive(str);
  }catch(std::exception& e) {
    //kick user out
    std::cout<<e.what()<<std::endl;
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

Connection ConnectionContainer::getConnection() {
	return m_connection;
}

std::string ConnectionContainer::getOutBuffer() {
  return m_protocol->send();
}