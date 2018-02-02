#ifndef MUD_PROTOCOL_H
#define MUD_PROTOCOL_H

#include "Protocol.h"
#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unistd.h>
namespace mudserver {
namespace connection {

class MudProtocol : public Protocol {
    std::string inBuffer;
    std::string broadcastBuffer;
    unsigned int maxBufSize;

public:
    MudProtocol();
    MudProtocol(unsigned int maxBuf);

    void receive(std::string str);

    std::string send();

    std::string broadcast(std::string);
};
}  // namespace connection
}  // namespace mudserver

#endif
