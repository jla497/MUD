// #include "Roll.h"
#include "entities/CombatComponent.h"
#include "CombatSimulation.h"

CombatComponent::CombatComponent(int armor, int thac0, Roll m_damageRollData,
                                 Roll m_hitRollData) {
    this->m_combatState = CombatStates::NOT_FIGHTING;
    this->m_armor = armor;
    this->m_thac0 = thac0;
    this->m_damageRollData = m_damageRollData;
    this->m_hitRollData = m_hitRollData;
    this->m_maxHealth = CombatSimulation::calcRoll(m_hitRollData);
    this->m_currentHealth = this->m_maxHealth;
}
CombatComponent::CombatComponent() {
    // TODO: use defaul values from config
    this->m_combatState = CombatStates::NOT_FIGHTING;
    this->m_armor = 0;
    this->m_thac0 = 0;
    this->m_damageRollData = {1, 1, 0};
    this->m_hitRollData = {1, 1, 0};
    this->m_maxHealth = CombatSimulation::calcRoll(m_hitRollData);
    this->m_currentHealth = this->m_maxHealth;
}

void CombatComponent::prepareToAttack() {
    // set nextCombatAbilityToBeUsed to the characters default attack(if their
    // is no weapon use the default Damageroll)
    // TODO:
    // this->nextCombatAbilityToBeUsed =
    // this->equippedWeapon->standardAttackAbility;
}

void CombatComponent::setArmor(int armor) { this->m_armor = armor; }
void CombatComponent::setThac0(int thac0) { this->m_thac0 = thac0; }
void CombatComponent::setDamageRoll(Roll damageRollData) {
    this->m_damageRollData = damageRollData;
}
void CombatComponent::setHitRoll(Roll hitRollData) {
    this->m_hitRollData = hitRollData;
    // recalculate health
    this->m_maxHealth = CombatSimulation::calcRoll(m_hitRollData);
    this->m_currentHealth = this->m_maxHealth;
}
CombatStates CombatComponent::getCombatState() const { return m_combatState; }
void CombatComponent::engageCombatState() {
    m_combatState = CombatStates::FIGHTING;
}
void CombatComponent::endCombatState() {
    m_combatState = CombatStates::NOT_FIGHTING;
}
Roll CombatComponent::getDamageRoll() const { return m_damageRollData; }
Roll CombatComponent::getHitRoll() const { return m_hitRollData; }
int CombatComponent::getArmor() const { return m_armor; }
int CombatComponent::getThac0() const { return m_thac0; }

bool CombatComponent::damage(int damageAmount) {
    if (damageAmount < 0) {
        heal(damageAmount * -1);
    }
    m_currentHealth -= damageAmount;
    if (m_currentHealth <= 0) {
        m_currentHealth = 0;
        return true;
    } else {
        return false;
    }
}

void CombatComponent::heal(int healAmount) {
    if (healAmount < 0) {
        damage(healAmount * -1);
    }
    m_currentHealth += healAmount;
    if (m_currentHealth > m_maxHealth) {
        m_currentHealth = m_maxHealth;
    }
}

std::string CombatComponent::getHealthDescription() const {
    return std::to_string(m_currentHealth) + "/" + std::to_string(m_maxHealth) +
           "hp";
}