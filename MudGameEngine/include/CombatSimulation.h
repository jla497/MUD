#ifndef COMBAT_SIM_H
#define COMBAT_SIM_H

// #include "actions/Action.h"
#include "gamemanager/GameManager.h"
#include "entities/CharacterEntity.h"

namespace CombatSimulation {
	
	using mudserver::gamemanager::GameManager;
	namespace CombatSimulation{
		static void resolveCombatRound(CharacterEntity& playerWhoIsAttacking,
			CharacterEntity&  playerWhoIsBeingAttacking,
			GameManager& gameManager);

	}
}
#endif