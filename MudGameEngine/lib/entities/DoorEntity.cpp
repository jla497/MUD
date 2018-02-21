#include <string>
#include <vector>

#include "entities/DoorEntity.h"

DoorEntity::DoorEntity(std::vector<std::string>& desc, std::string& dir,
                       std::vector<std::string>& keywords, unsigned int to)
    : Entity::Entity(),
      m_desc(desc),
      m_dir(dir),
      m_keywords(keywords),
      m_to(to) {}

unsigned int DoorEntity::getDestRoomId() const { return m_to; }

std::vector<std::string> DoorEntity::getDesc() const { return m_desc; }

std::string DoorEntity::getDir() const { return m_dir; }

std::vector<std::string> DoorEntity::getKeywords() const { return m_keywords; }