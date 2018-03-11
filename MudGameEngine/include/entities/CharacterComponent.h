#ifndef CHARACTER_COMPONENT_H
#define CHARACTER_COMPONENT_H
#include "Roll.h"
// #include "entities/Entity.h"
// #include "entities/ObjectEntity.h"

/**
CharacterComponent defines the common interface for all components a Character
holds
*/
class CharacterComponent {
  public:
    virtual void update(float deltaTime) {
        // update character simulation(ai, etc)
    }
};

#endif
