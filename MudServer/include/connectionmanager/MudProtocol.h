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

class MudProtocol final : public Protocol {
    std::string inBuffer;
    std::string broadcastBuffer;
    unsigned int maxBufSize{};

  public:
    MudProtocol();
    explicit MudProtocol(const unsigned int maxBuf);

    void receive(std::string str) override;

    std::string send() override;

    std::string broadcast(std::string) override;
};
} // namespace connection
} // namespace mudserver

#endif
