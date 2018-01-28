#include <string>
#include <vector>

#include "Entity.h"
#include "Reset.h"

Reset::Reset(int id,std::string action,std::string comment, int slot,
			 int limit,int roomId) : 
    m_id(id),
    m_action(action),
    m_comment(comment),
    m_slot(slot),
    m_limit(limit),
    m_roomId(roomId) {
}

