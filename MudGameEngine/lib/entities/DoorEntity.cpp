#include <string>
#include <vector>

#include "DoorEntity.h"

DoorEntity::DoorEntity(std::string& desc, std::string& dir,
                       std::vector<std::string>& keywords, unsigned int to)
    : m_desc(desc), m_dir(dir), m_keywords(keywords), m_to(to) {}

unsigned int DoorEntity::getDestRoomId() { return m_to; }