#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

#include "UniqueId.h"

/*Entity Interface for making other types of entities like:
  players, rooms, objects*/
class Entity {
  protected:
    // Unique id that every created entity has
    UniqueId m_entityId{};

  public:
    Entity() = default;
    Entity(const Entity&) = default;
    Entity &operator=(const Entity&) = default;
    Entity(Entity&&) = default;
    Entity &operator=(Entity&&) = default;
    virtual ~Entity() = default;

    UniqueId getEntityId() const;
};

#endif