#ifndef PROTOCOL_H
#define PROTOCOL_H


#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <exception>
#include <iostream>

/*Application protocol interface*/
class Protocol {

  // std::string in_buffer;
  // std::string out_buffer;
  // int max_buffer_size;

public:
  //application specific formatting done here for inputs
  virtual void receive(std::string str) = 0;

  //application specific formatting done here for output strings
  virtual std::string send() = 0;

  //applicaiton specific formatting for broadcasts
  virtual std::string broadcast(std::string) = 0;
};
#endif
