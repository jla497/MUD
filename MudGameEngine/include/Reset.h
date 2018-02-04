#ifndef RESET_H
#define RESET_H
#include <string>
#include <vector>

#include "entities/Entity.h"

class Reset {
public:
    Reset(int id, std::string action, std::string comment, std::string state, 
    	int slot, int limit,int roomID);

private:
    // TODO: figure out Id, it seems that Id may refer to different things
    // depending on the reset action.
    // If the action is equip, than it is talking about the object with the id.
    int id;
    // maybe change action from string to its own type
    std::string action;
    std::string comment;
    std::string state;
    int slot;
    int limit;
    int roomID;
};
#endif
