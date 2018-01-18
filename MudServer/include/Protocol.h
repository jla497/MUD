#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <exception>
#include <iostream>

class Protocol {

  // std::string in_buffer;
  // std::string out_buffer;
  // int max_buffer_size;

public:
  virtual std::string receive(std::string& str)= 0;

  virtual void sendToBuffer(std::string& str) = 0;

  virtual std::string send() = 0;

  virtual std::string broadcast() = 0;
};
#endif