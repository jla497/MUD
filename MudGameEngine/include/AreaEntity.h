#ifndef AREA_ENTITY_H
#define AREA_ENTITY_H

#include "Entity.h"
#include "RoomEntity.h"

class AreaEntity : public Entity {
   private:
    // add unique id
    std::string m_name;
    std::vector<RoomEntity> m_rooms;

   public:
    AreaEntity(UniqueId& id, std::string& name,
               std::vector<RoomEntity> rooms);
};

#endif
