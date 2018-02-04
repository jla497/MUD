#ifndef AREA_ENTITY_H
#define AREA_ENTITY_H

#include "Entity.h"
#include "RoomEntity.h"

class AreaEntity : public Entity {
   private:
    // add unique id
    std::string m_name;
    std::vector<std::unique_ptr<RoomEntity>> m_rooms;

   public:
    AreaEntity(std::string& name,
               std::vector<std::unique_ptr<RoomEntity>> rooms);


    std::vector<std::unique_ptr<RoomEntity>>& getAllRooms();

    std::string getName();
};

#endif
