#include <string>
#include <utility>
#include <vector>

#include "entities/DoorEntity.h"

DoorEntity::DoorEntity(std::vector<std::string> desc, std::string dir,
                       std::vector<std::string> keywords, unsigned int to)
    : Entity::Entity(), m_desc(std::move(desc)), m_dir(std::move(dir)),
      m_keywords(std::move(keywords)), m_to(to) {}

unsigned int DoorEntity::getDestRoomId() const { return m_to; }

std::vector<std::string> DoorEntity::getDesc() const { return m_desc; }

std::string DoorEntity::getDir() const { return m_dir; }

std::vector<std::string> DoorEntity::getKeywords() const { return m_keywords; }
