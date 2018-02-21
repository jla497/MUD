/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////

#include <unistd.h>

#include "ChatWindow.h"
#include "Client.h"
#include "configparser/ConfigParser.h"
#include <boost/optional/optional.hpp>

using networking::Port;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n%s <config_file_path>\ne.g. %s config.yaml\n", argv[0],
               argv[0]);
        return 1;
    }

    auto configData = parseConfigFile(argv[1]);

    if (configData) {
        auto url = configData->url;
        auto port = configData->clientPort;
        networking::Client client{url.c_str(), port.c_str()};

        bool done = false;
        auto onTextEntry = [&done, &client](std::string text) {
            if ("exit" == text || "quit" == text) {
                done = true;
            } else {
                client.send(text);
            }
        };

        ChatWindow chatWindow(onTextEntry);
        while (!done && !client.isDisconnected()) {
            try {
                client.update();
            } catch (std::exception &e) {
                chatWindow.displayText("Exception from Client update:");
                chatWindow.displayText(e.what());
                done = true;
            }

            auto response = client.receive();
            if (!response.empty()) {
                chatWindow.displayText(response);
            }
            chatWindow.update();
        }

        return 0;
    }
