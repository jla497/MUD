#include <string>
#include <vector>

#include "entities/DoorEntity.h"

DoorEntity::DoorEntity(std::vector<std::string>& desc,
                       std::string& dir, std::vector<std::string>& keywords,
                       unsigned int to)
    : Entity::Entity(),
      m_desc(desc),
      m_dir(dir),
      m_keywords(keywords),
      m_to(to) {}

unsigned int DoorEntity::getDestRoomId() { return m_to; }