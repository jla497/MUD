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
  private:
    // Unique id that every created entity has
    UniqueId m_entityId;

  public:
    Entity();

    const UniqueId &getEntityId() const;

    // default destructor does nothing
    // if you make a virtual destructor, does compiler
    // remove your default destructors?
    virtual ~Entity(){};
};

#endif