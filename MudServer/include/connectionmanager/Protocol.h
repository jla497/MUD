#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unistd.h>

namespace mudserver {
namespace connection {

/*Application protocol interface*/
class Protocol {
public:
    // application specific formatting done here for inputs
    virtual void receive(std::string str) = 0;

    // application specific formatting done here for output strings
    virtual std::string send() = 0;

    // applicaiton specific formatting for broadcasts
    virtual std::string broadcast(std::string) = 0;
};
}
}

#endif
