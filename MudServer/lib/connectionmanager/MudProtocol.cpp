#include "connectionmanager/MudProtocol.h"

namespace mudserver {
namespace connection {

MudProtocol::MudProtocol(){}

MudProtocol::MudProtocol(const unsigned int max_buf) : maxBufSize(max_buf) {}

void MudProtocol::receive(std::string str) {
    for (auto &c : str) {
        inBuffer.append(1, c);
    }

    inBuffer.append("\n");
}

std::string MudProtocol::send() {
    if (inBuffer.empty())
        return {};

    constexpr auto prefixes = "";
    constexpr auto suffixes = "";

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
} // namespace connection
} // namespace mudserver
