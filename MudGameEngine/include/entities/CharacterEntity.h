#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include "Entity.h"

enum class CombatStates{
	NOT_FIGHTING,
	FIGHTING
};

class CharacterEntity : public Entity {
   private:
   public:
   CharacterEntity();
   CombatStates combatState;

};

#endif
