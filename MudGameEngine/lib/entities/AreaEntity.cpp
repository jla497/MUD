#include <string>
#include <vector>

#include "AreaEntity.h"

AreaEntity::AreaEntity(std::string& name, std::vector<unsigned int>& rooms)
    : m_name(name), m_rooms(rooms) {}