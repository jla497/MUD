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

int CombatSimulation::calcRoundDamage(Roll damageRoll, Roll hitRoll) {
    int attackvalue = calcRoll(damageRoll);
    int hitValue = calcRoll(hitRoll);

    // ignore hit for now
    int netDamage = attackvalue;
    return netDamage;
}

void CombatSimulation::resolveCombatRound(
    CharacterEntity &characterWhoIsAttacking,
    CharacterEntity &characterWhoIsBeingAttacked, GameManager &gameManager) {

    // get fighters combat components
    CombatComponent *attackingCharactersCombatComponent =
        characterWhoIsAttacking.getCombatComponent();
    CombatComponent *attackedCharactersCombatComponent =
        characterWhoIsBeingAttacked.getCombatComponent();

    gameManager.sendCharacterMessage(characterWhoIsAttacking.getEntityId(),
                                     "Starting combat round");
    gameManager.sendCharacterMessage(characterWhoIsBeingAttacked.getEntityId(),
                                     "Starting combat round");

    // set combat states of fighters to fighting
    attackingCharactersCombatComponent->engageCombatState();
    attackedCharactersCombatComponent->engageCombatState();

    // TODO: use CombatAbilities rather than just raw roll values
    // A CombatAbility should encapsulate the damage dealth along site any
    // effects it might apply (ex a fireball might apply a burning effect on the
    //target)
    int damageAmount =
        calcRoundDamage(attackingCharactersCombatComponent->getDamageRoll(),
                        (attackedCharactersCombatComponent->getHitRoll()));

    // deal damage
    bool enemyWasKilled = attackedCharactersCombatComponent->damage(5);

    // send messages to characters fighting
    gameManager.sendCharacterMessage(
        characterWhoIsAttacking.getEntityId(),
        "You attack " + characterWhoIsBeingAttacked.getShortDesc() +
            " and do " + std::to_string(damageAmount) + " damage");

    gameManager.sendCharacterMessage(
        characterWhoIsBeingAttacked.getEntityId(),
        "You are attacked by " + characterWhoIsAttacking.getShortDesc() +
            " and take " + std::to_string(damageAmount) + " damage");

    // exit combat state and remove Character from world if the attacked dies
    if (enemyWasKilled) {
        attackingCharactersCombatComponent->endCombatState();
        attackedCharactersCombatComponent->endCombatState();

        gameManager.sendCharacterMessage(
            characterWhoIsAttacking.getEntityId(),
            "You killed " + characterWhoIsBeingAttacked.getShortDesc());
        gameManager.sendCharacterMessage(
            characterWhoIsBeingAttacked.getEntityId(),
            "You were killed by " + characterWhoIsAttacking.getShortDesc());

        // calculate rewards and give them to the attacker
        int goldToGive = characterWhoIsBeingAttacked.getGold();
        int expToGive = characterWhoIsBeingAttacked.getExp();
        characterWhoIsAttacking.addGold(goldToGive);
        characterWhoIsAttacking.incExp(expToGive);

        // remove killed character from game state
        gameManager.getState().killCharacter(characterWhoIsBeingAttacked);
    }

    gameManager.sendCharacterMessage(characterWhoIsAttacking.getEntityId(),
                                     "Ending combat round");
    gameManager.sendCharacterMessage(characterWhoIsBeingAttacked.getEntityId(),
                                     "Ending combat round");
}
