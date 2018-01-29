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
    std::string inBuffer;
    std::string broadcastBuffer;
    int maxBufSize;

   public:
    MudProtocol();
    MudProtocol(int maxBuf);

    void receive(std::string str);

    std::string send();

    std::string broadcast(std::string);
};
#endif
