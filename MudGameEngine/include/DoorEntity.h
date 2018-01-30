#ifndef DOOR_ENTITY_H
#define DOOR_ENTITY_H

#include "Entity.h"

class DoorEntity : public Entity {
   private:
    std::vector<std::string> m_desc;
    std::string m_dir;  // didn't enum dir, could be arbitrary
    std::vector<std::string> m_keywords;
    unsigned int m_to;  // Room this door leads to

    // https://stackoverflow.com/questions/15517991/search-a-vector-of-objects-by-object-attribute
    // use std::find_if instead
    // find_to(std::string dir) : dir_(dir) {}
    // bool operator()(Door& door) {return door.dir == dir_;}
   public:
    DoorEntity(UniqueId& id, std::vector<std::string>& desc, std::string& dir,
               std::vector<std::string>& keywords, unsigned int to);

    unsigned int getDestRoomId();
};

#endif