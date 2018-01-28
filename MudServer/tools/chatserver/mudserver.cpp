/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "Server.h"

#include "ConnectionManager.h"

#include <sstream>

#include <unistd.h>

#include <iostream>

using namespace networking;

ConnectionManager m_manager;

//Welcome msg for new clients
void onConnect(Connection c) {
  printf("New connection found: %lu\n", c.id);
  m_manager.addConnection(c);
}

void onDisconnect(Connection c) {
  printf("Connection lost: %lu\n", c.id);
}

// std::deque<Message> buildOutgoing(const std::string& log) {
//   std::deque<Message> outgoing;
  
//   for (auto client : clients) {
//     outgoing.push_back({client, log});
//   }
  
//   return outgoing;
// }

void testConnectionManager( Server& server, ConnectionManager& c_manager, const std::deque<Message> &incoming) {

  c_manager.passMessages(incoming);

  c_manager.sendMessages(server);

  c_manager.dropConnection(server);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage:\n%s <port>\ne.g. %s 4002\n", argv[0], argv[0]);
    return 1;
  }

  bool done = false;

  unsigned short port = std::stoi(argv[1]);

  Server server{port, onConnect, onDisconnect};

  std::cout << "---------------------MUD Server Console---------------------"<<std::endl;
  
  while (!done) {
    try {
      server.update();
    } catch (std::exception& e) {
      printf("Exception from Server update:\n%s\n\n", e.what());
      done = true;
    }

    auto incoming = server.receive();
    
    testConnectionManager(server, m_manager, incoming);
    
    sleep(1);
  }

  return 0;
}

