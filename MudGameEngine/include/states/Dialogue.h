//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_DIALOGUE_H
#define ADVENTURE2018_DIALOGUE_H
#include <unordered_map>

class Dialogue {

    static std::unordered_map<std::string, std::string> dialogueMap;

public:
    std::string getResponse(std::string arg);
    void setDialogue(std::string arg, std::string response);
};
#endif // ADVENTURE2018_CHARACTERCONTROLLER_H
