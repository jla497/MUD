#include <string>
#include <vector>

#include "Reset.h"

  Reset::Reset(int id,std::string action,std::string comment,int slot,int limit,int roomID)
  {
      this->id = id;
      this->action = action;
      this->comment = comment;
      this->slot = slot;
      this->limit = limit;
      this->roomID = roomID;
  }
