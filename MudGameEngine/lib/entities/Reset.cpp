#include <string>
#include <utility>
#include <vector>

#include "Reset.h"

Reset::Reset(int id, std::string action, std::string comment, std::string state,
             int slot, int limit, int roomID)
    : id{id}, action{std::move(action)}, comment{std::move(comment)},
      state{std::move(state)}, slot{slot}, limit{limit}, roomID{roomID} {}
