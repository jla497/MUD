//Wrapper function for testing mudserver methods

#include "Server.h"

#include "ConnectionManager.h"

#include <sstream>

#include <unistd.h>

#include <iostream>

using namespace networking;

//globals
ConnectionList connect_list;

ConnectionManager connectionManager = ConnectionManager(&connect_list);

//temporary stub for the GameManager class
struct GameManager {
    std::string broadcast_msg;

    std::string echoBack() {
      broadcast_msg.clear();
      std::stringstream ss;

      for(auto& conn: connect_list) {
        std::string user_msg = conn->getHandler().getUserInput();
        std::string user_name = conn->username;   
        if(!user_msg.empty()) 
          ss << user_name <<": "<<user_msg<<"\n";
      }

      broadcast_msg = ss.str();
      return broadcast_msg;
    }
};

struct GameManager gameManager;

void onConnect(Connection c) {
  printf("New connection found: %lu\n", c.id);
  connectionManager.addConnection(c);
}

void onDisconnect(Connection c) {
  printf("Connection lost: %lu\n", c.id);
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

    connectionManager.passMessages(incoming);

    connectionManager.sendMessages(server);

    auto broadcast_msg = gameManager.echoBack();

    connectionManager.broadCast(server, broadcast_msg);

    connectionManager.dropConnection(server);
    
    sleep(1);
  }

  return 0;
}

