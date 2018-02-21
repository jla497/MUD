#include <string>
#include <vector>

#include "Reset.h"

Reset::Reset(int id, std::string action, std::string comment, std::string state,
             int slot, int limit, int roomID)
    : id{id}, action{action}, comment{comment}, state{state}, slot{slot},
      limit{limit}, roomID{roomID} {}
