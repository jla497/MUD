#include "CombatSimulation.h"

int CombatSimulation::calcRoll(Roll roll) {
    int rollValue = 0;
    for (int i = 0; i < roll.numOfDie; ++i) {
        // generate roll in range [1,sizeOfDie]
        rollValue += rand() % roll.sizeOfDie + 1;
    }
    rollValue += roll.rollModifier;
    return rollValue;
}

int CombatSimulation::calcMaxPossibleRoll(Roll roll) {
    return roll.numOfDie * roll.sizeOfDie + roll.rollModifier;
}

int CombatSimulation::calcRoundDamage(Roll damageRoll) {
    int attackvalue = calcRoll(damageRoll);
    int netDamage = attackvalue;
    return netDamage;
}

void CombatSimulation::resolveCombatRound(CharacterEntity &attacker,
                                          CharacterEntity &defender,
                                          GameManager &gameManager) {

    // get fighters combat components
    CombatComponent *attackersCombatComponent = attacker.getCombatComponent();
    CombatComponent *defendersCombatComponent = defender.getCombatComponent();

    if (attackersCombatComponent == defendersCombatComponent) {
        gameManager.sendCharacterMessage(attacker.getEntityId(),
                                         "You cannot attack yourself!");
        return;
    }

    gameManager.sendCharacterMessage(attacker.getEntityId(),
                                     "Starting combat round");
    gameManager.sendCharacterMessage(defender.getEntityId(),
                                     "Starting combat round");

    // set combat states of fighters to fighting
    attackersCombatComponent->engageCombatState();
    defendersCombatComponent->engageCombatState();

    // TODO: use CombatAbilities rather than just raw roll values
    // A CombatAbility should encapsulate the damage dealt along side any
    // effects it might apply (ex a fireball might apply a burning effect on the
    // target)
    int damageAmount =
        calcRoundDamage(attackersCombatComponent->getDamageRoll());

    // deal damage
    defendersCombatComponent->damage(damageAmount);
    bool enemyWasKilled = defendersCombatComponent->isCharacterDead();

    // send messages to characters fighting
    gameManager.sendCharacterMessage(
        attacker.getEntityId(), "You attack " + defender.getShortDesc() +
                                    " and do " + std::to_string(damageAmount) +
                                    " damage");

    gameManager.sendCharacterMessage(
        defender.getEntityId(), "You are attacked by " +
                                    attacker.getShortDesc() + " and take " +
                                    std::to_string(damageAmount) + " damage");

    // exit combat state and remove Character from world if the attacked dies
    if (enemyWasKilled) {
        attackersCombatComponent->endCombatState();
        defendersCombatComponent->endCombatState();

        gameManager.sendCharacterMessage(
            attacker.getEntityId(), "You killed " + defender.getShortDesc());
        gameManager.sendCharacterMessage(defender.getEntityId(),
                                         "You were killed by " +
                                             attacker.getShortDesc());

        // calculate rewards and give them to the attacker
        // TODO: have a formula/function for calculating rewards
        int goldToGive = defender.getGold();
        int expToGive = defender.getExp();
        defender.subtractGold(goldToGive);

        attacker.addGold(goldToGive);
        attacker.incExp(expToGive);

        // remove killed character from game state
        gameManager.getState().killCharacter(defender);
    }

    gameManager.sendCharacterMessage(attacker.getEntityId(),
                                     "Ending combat round");
    gameManager.sendCharacterMessage(defender.getEntityId(),
                                     "Ending combat round");
}
