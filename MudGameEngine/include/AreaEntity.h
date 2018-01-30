#ifndef AREA_ENTITY_H
#define AREA_ENTITY_H

#include "Entity.h"

class AreaEntity : public Entity {
   private:
    // add unique id
    std::string m_name;
    std::vector<unsigned int> m_rooms;

   public:
    AreaEntity(UniqueId& id, std::string& name,
               std::vector<unsigned int> rooms);
};

#endif
