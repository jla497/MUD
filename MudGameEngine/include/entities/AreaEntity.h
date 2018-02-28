#ifndef AREA_ENTITY_H
#define AREA_ENTITY_H

#include <deque>

#include "Entity.h"
#include "RoomEntity.h"

class AreaEntity : public Entity {
  private:
    // add unique id
    std::string m_name;
    std::deque<RoomEntity> m_rooms;

  public:
    AreaEntity() = default;

    AreaEntity(const std::string &name, std::deque<RoomEntity> rooms);

    std::deque<RoomEntity> &getAllRooms();

    std::string getName() const;
};

#endif
