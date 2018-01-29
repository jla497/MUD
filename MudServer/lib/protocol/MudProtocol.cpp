#include "MudProtocol.h"

MudProtocol::MudProtocol() : maxBufSize(512) {}

MudProtocol::MudProtocol(int max_buf) : maxBufSize(max_buf) {}

void MudProtocol::receive(std::string str) {
  //pass only alphanumeric characters, backspace nad cr

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
    if (inBuffer.empty()) return "";

    std::string res;
    std::stringstream ss;

    auto prefixes = "";

    auto suffixes = "\n";

    ss << prefixes << inBuffer << suffixes;

    res = ss.str();

    // std::cout << res << std::endl;
    inBuffer.clear();

    return res;
}

//any protocol-specific text formatting here
std::string MudProtocol::broadcast(std::string broadcast) {

  if (broadcast.empty())
    return "";

  broadcastBuffer = broadcast;

  std::string res;

  std::stringstream ss;

  auto prefixes = "[ MudProtocol-specific broadcast formatting happens here: ]\n";

  auto suffixes = "\n";

  ss << prefixes << broadcastBuffer << suffixes;

  res = ss.str();

  broadcastBuffer.clear();

  return res;
}
