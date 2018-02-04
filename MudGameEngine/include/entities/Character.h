#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"

enum class CombatStates{
	NOT_FIGHTING,
	FIGHTING
};

class Character : public Entity {
   private:
   public:
   Character();
   CombatStates combatState;

};

#endif
