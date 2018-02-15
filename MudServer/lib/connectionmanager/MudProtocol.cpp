#include "connectionmanager/MudProtocol.h"

namespace mudserver {
namespace connection {

MudProtocol::MudProtocol() : maxBufSize(512) {}

MudProtocol::MudProtocol(unsigned int max_buf) : maxBufSize(max_buf) {}

void MudProtocol::receive(std::string str) {
    // pass only alphanumeric characters, backspace nad cr

    for (auto& c : str) {
        if ((std::isalnum(c) || std::isspace(c)) &&
            inBuffer.length() < maxBufSize) {
            inBuffer.append(1, c);
        }

        if (inBuffer.length() >= maxBufSize) {
            throw std::runtime_error("buffer overflow");
        }
    }

    return;
}

std::string MudProtocol::send() {
    if (inBuffer.empty())
        return {};

    constexpr auto prefixes = "";
    constexpr auto suffixes = "\n";

    std::ostringstream oss;
    oss << prefixes << inBuffer << suffixes;
    inBuffer.clear();
    return oss.str();
}

// any protocol-specific text formatting here
std::string MudProtocol::broadcast(std::string broadcast) {
    if (broadcast.empty())
        return {};
    broadcastBuffer = broadcast;

    constexpr auto prefixes =
        "[ MudProtocol-specific broadcast formatting happens here: ]\n";
    constexpr auto suffixes = "\n";

    std::ostringstream oss;
    oss << prefixes << broadcastBuffer << suffixes;
    broadcastBuffer.clear();
    return oss.str();
}
}
}