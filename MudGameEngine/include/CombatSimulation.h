#ifndef COMBAT_SIM_H
#define COMBAT_SIM_H

#include "entities/CharacterEntity.h"
#include "gamemanager/GameManager.h"

namespace CombatSimulation {
using mudserver::gamemanager::GameManager;

void resolveCombatRound(CharacterEntity &playerWhoIsAttacking,
                        CharacterEntity &playerWhoIsBeingAttacking,
                        GameManager &gameManager);

int calcRoundDamage(Roll damageRoll);
int calcRoll(Roll roll);
int calcMaxPossibleRoll(Roll roll);

} // namespace CombatSimulation
#endif
