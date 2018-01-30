#include "MudProtocol.h"

MudProtocol::MudProtocol(): max_buffer_size(512) {}

MudProtocol::MudProtocol(int max_buf): max_buffer_size(max_buf) {}

<<<<<<< HEAD
std::string MudProtocol::receive(const std::string& str) {
=======
void MudProtocol::receive(std::string str) {
>>>>>>> master
  //pass only alphanumeric characters, backspace nad cr

  for (auto& c : str) {

    if ((std::isalnum(c) || std::isspace(c)) && in_buffer.length() < max_buffer_size) {
      in_buffer.append(1, c);
    }

    if (in_buffer.length() >= max_buffer_size) {
      throw std::runtime_error("buffer overflow");
    }
  }

<<<<<<< HEAD
  auto res = in_buffer;

  in_buffer.clear();

  return res;
 
}

void MudProtocol::sendToBuffer(const std::string& str) {
  out_buffer.append(str);
=======
  return;
>>>>>>> master
}

std::string MudProtocol::send() {

  if (in_buffer.empty())
    return "";

  std::string res;
  std::stringstream ss;

  auto prefixes = "";

  auto suffixes = "\n";

  ss << prefixes << in_buffer << suffixes;

  res = ss.str();

  // std::cout << res << std::endl;
  in_buffer.clear();

  return res;
}

//any protocol-specific text formatting here
std::string MudProtocol::broadcast(std::string broadcast) {

  if (broadcast.empty())
    return "";

  broadcast_buffer = broadcast;

  std::string res;

  std::stringstream ss;

  auto prefixes = "[ MudProtocol-specific broadcast formatting happens here: ]\n";

  auto suffixes = "\n";

  ss << prefixes << broadcast_buffer << suffixes;

  res = ss.str();

  broadcast_buffer.clear();

  return res;
}
