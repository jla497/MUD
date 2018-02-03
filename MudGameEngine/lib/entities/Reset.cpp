#include <string>
#include <vector>

#include "Reset.h"

Reset::Reset(int id, std::string action, std::string comment, int slot,
             int limit, int roomID)
    : id{id},
      action{action},
      comment{comment},
      slot{slot},
      limit{limit},
      roomID{roomID} {}
