//Wrapper function for testing mudserver methods

#include "Server.h"

#include "ConnectionManager.h"

#include <sstream>

#include <unistd.h>

#include <iostream>

using namespace networking;

//globals



int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage:\n%s <port>\ne.g. %s 4002\n", argv[0], argv[0]);
    return 1;
  }

  unsigned short port = std::stoi(argv[1]);

  ConnectionManager connectionManager;

  connectionManager.run();

  return 0;
}

