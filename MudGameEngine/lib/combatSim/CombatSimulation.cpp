#include "CombatSimulation.h"

#define NULL_CHAR_NAME ""

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

    //if you are already in combat and are trying to attack someone
    //who is not your enemy, exit out.
    if(attackersCombatComponent->getEnemiesName() != NULL_CHAR_NAME &&
        attackersCombatComponent->getEnemiesName() != defendersCombatComponent->getOwnersName()){
        gameManager.sendCharacterMessage(attacker.getEntityId(),
                                     "You are already fighting someone else");
        return;   
    }
    //check if your enemy is already in combat with someone else
    if(defendersCombatComponent->getEnemiesName() != NULL_CHAR_NAME &&
        defendersCombatComponent->getEnemiesName() != attackersCombatComponent->getOwnersName()){
        gameManager.sendCharacterMessage(attacker.getEntityId(),
                                     "Your target is already fighting someone");
        return;
    }

    gameManager.sendCharacterMessage(attacker.getEntityId(),
                                     "Starting combat round");
    gameManager.sendCharacterMessage(defender.getEntityId(),
                                     "Starting combat round");

    // set combat states of fighters to fighting
    attackersCombatComponent->engageCombatState();
    defendersCombatComponent->engageCombatState();

    //store enemy names
    attackersCombatComponent->setEnemiesName(defendersCombatComponent->
        getOwnersName());
    defendersCombatComponent->setEnemiesName(attackersCombatComponent->
        getOwnersName());

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

        //clear enemy names
        attackersCombatComponent->setEnemiesName(NULL_CHAR_NAME);
        defendersCombatComponent->setEnemiesName(NULL_CHAR_NAME);

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
