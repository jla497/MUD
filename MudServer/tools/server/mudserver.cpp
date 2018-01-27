//Wrapper function for testing mudserver methods

#include <sstream>
#include <unistd.h>
#include <iostream>
#include <memory>

#include "Server.h"
#include "ConnectionManager.h"
#include "gamemanager/GameManager.h"


int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage:\n%s <port>\ne.g. %s 4002\n", argv[0], argv[0]);
    return 1;
  }

  unsigned short port = std::stoi(argv[1]);

  mudserver::gamemanager::GameManager gameManager{};
  
  
  std::cout << "---------------------MUD Server Console---------------------"<<std::endl;
  
  gameManager.mainLoop();

  return 0;
}

