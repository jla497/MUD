#ifndef MUD_PROTOCOL_H
#define MUD_PROTOCOL_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <exception>
#include <iostream>
#include "Protocol.h"

class MudProtocol: public Protocol {

  std::string in_buffer;
  std::string out_buffer;
  std::string broadcast_buffer;
  int max_buffer_size;;

public:
  MudProtocol();
  MudProtocol(int max_buf);

  void receive(std::string str);

  std::string send();

  std::string broadcast(std::string);
};
#endif
