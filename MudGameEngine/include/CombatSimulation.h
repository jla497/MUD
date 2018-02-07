#ifndef COMBAT_SIM_H
#define COMBAT_SIM_H

// #include "actions/Action.h"
#include "gamemanager/GameManager.h"
#include "entities/CharacterEntity.h"

namespace CombatSimulation {
	using mudserver::gamemanager::GameManager;

	void resolveCombatRound(CharacterEntity& playerWhoIsAttacking,
		CharacterEntity&  playerWhoIsBeingAttacking,
		GameManager& gameManager);

	int calcRoundDamage(Roll damageRoll, Roll hitRoll);
	int calcRoll(Roll roll);

}
#endif
