//
// Created by jla497 on 13/03/18.
//

#include "states/Dialogue.h"
std::unordered_map<std::string, std::string> Dialogue::dialogueMap = {
        {"hey hello", "say hello"},
        {"who where from", "say I am %me" },
        {"give stuff give things", "say you cant have my stuff"},
        {"idiot, stupid, dumb", "say kick your self"}
};

std::string Dialogue::getResponse(std::string arg) {
    for(auto& pair : dialogueMap) {
        if(pair.first.find(arg) != std::string::npos) {
            auto reply = pair.second;
            return reply;
        }
    }
    return std::string{};
}

void Dialogue::setDialogue(std::string arg, std::string response) {
    dialogueMap[arg] = response;
}