// #include "Roll.h"
#include "entities/CombatComponent.h"
#include "CombatSimulation.h"

CombatComponent::CombatComponent(int armor, int thac0, Roll damageRoll,
                                 Roll maxHitPointRoll) {
    this->combatState = CombatStates::NOT_FIGHTING;
    this->armor = armor;
    this->thac0 = thac0;
    this->damageRoll = damageRoll;
    this->maxHitPointRoll = maxHitPointRoll;
    this->maxHealth = CombatSimulation::calcRoll(maxHitPointRoll);
    this->currentHealth = this->maxHealth;
}
CombatComponent::CombatComponent() : CombatComponent(0, 0, {1, 1, 0},{1, 1, 0}){
    // TODO: use default values from config rather than hardcoded values
}

void CombatComponent::prepareToAttack() {
    // set nextCombatAbilityToBeUsed to the characters default attack(if their
    // is no weapon use the default Damageroll)
    // TODO:
    // this->nextCombatAbilityToBeUsed =
    // this->equippedWeapon->standardAttackAbility;
}

void CombatComponent::setArmor(int armor) { this->armor = armor; }
void CombatComponent::setThac0(int thac0) { this->thac0 = thac0; }
void CombatComponent::setDamageRoll(Roll damageRollData) {
    this->damageRoll = damageRollData;
}
void CombatComponent::setHitRoll(Roll maxHitPointRoll) {
    this->maxHitPointRoll = maxHitPointRoll;
    // recalculate health
    this->maxHealth = CombatSimulation::calcRoll(maxHitPointRoll);
    this->currentHealth = this->maxHealth;
}
CombatStates CombatComponent::getCombatState() const { return combatState; }
void CombatComponent::engageCombatState() {
    combatState = CombatStates::FIGHTING;
}
void CombatComponent::endCombatState() {
    combatState = CombatStates::NOT_FIGHTING;
}
Roll CombatComponent::getDamageRoll() const { return damageRoll; }
Roll CombatComponent::getHitRoll() const { return maxHitPointRoll; }
int CombatComponent::getArmor() const { return armor; }
int CombatComponent::getThac0() const { return thac0; }

void CombatComponent::damage(int damageAmount) {
    if (damageAmount < 0) {
        //heal(damageAmount * -1);
        return;
    }
    currentHealth -= damageAmount;
     if (currentHealth <= 0) {
        currentHealth = 0;
    }   
    // if (currentHealth <= 0) {
    //     currentHealth = 0;
    //     return true;
    // } else {
    //     return false;
    // }
}

bool CombatComponent::isCharacterDead(){
    if (currentHealth <= 0) {
        return true;
    } else {
        return false;
    }
}

void CombatComponent::heal(int healAmount) {
    if (healAmount < 0) {
        //damage(healAmount * -1);
        return;
    }
    currentHealth += healAmount;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

std::string CombatComponent::getHealthDescription() const {
    return std::to_string(currentHealth) + "/" + std::to_string(maxHealth) +
           "hp";
}