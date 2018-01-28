#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

/*Entity Interface for making other types of entities like:
  players, rooms, objects*/
class Entity {
   protected:
    static unsigned int nextUniqueId;

   private:
    // typeId
    int m_entityId;

    // std::string m_desc;

   public:
    Entity();

    unsigned int getEntityId();

    // std::string getDesc();

    // default destructor does nothing
    virtual ~Entity(){};
};

unsigned int Entity::nextUniqueId = 1;

#endif