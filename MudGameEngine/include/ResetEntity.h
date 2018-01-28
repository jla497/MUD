#ifndef RESET_H
#define RESET_H
#include <string>
#include <vector>

#include "Entity.h"

class Reset : public Entity {
   private:
    // TODO: figure out Id, it seems that Id may refer to different things
    // depending on the reset action.
    // If the action is equip, than it is talking about the object with the id.
    int m_id;
    // maybe change from string to its own type
    std::string m_action;
    std::string m_comment;
    int m_slot;
    int m_limit;
    int m_roomId;

   public:
    Reset(int id, std::string action, std::string comment, int slot, int limit,
          int roomId);
};
#endif
