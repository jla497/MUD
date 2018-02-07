// #include "Roll.h"
#include "entities/CombatComponent.h"

CombatComponent::CombatComponent(int armor, int thac0, Roll m_damageRollData, Roll m_hitRollData){
	this->m_combatState = CombatStates::NOT_FIGHTING;
	this->m_armor = armor;
	this->m_thac0 = thac0;
	this->m_damageRollData = m_damageRollData;
    this->m_hitRollData = m_hitRollData;
}
CombatComponent::CombatComponent(){
	this->m_combatState = CombatStates::NOT_FIGHTING;
	this->m_armor = 0;
	this->m_thac0 = 0;
	this->m_damageRollData = {1,1,0};
    this->m_hitRollData = {1,1,0};
}

void prepareToAttack(){
	//set nextCombatAbilityToBeUsed to the characters default attack(if their is no weapon use the default Damageroll)
}

void die(){
	//remove from play
	//if the character is controlled by a player notify them

}



void CombatComponent::setArmor(int armor){
	this->m_armor = armor;
}
void CombatComponent::setThac0(int thac0){
	this->m_thac0 = thac0;
}
void CombatComponent::setDamageRoll(Roll damageRollData){
	this->m_damageRollData = damageRollData;
}
void CombatComponent::setHitRoll(Roll hitRollData){
	this->m_hitRollData = hitRollData;
}
CombatStates CombatComponent::getCombatState() const { 
	return m_combatState; 
}
void CombatComponent::engageCombatState() {
    this->m_combatState = CombatStates::FIGHTING;
}
void CombatComponent::endCombatState() {
    this->m_combatState = CombatStates::NOT_FIGHTING;
}
Roll CombatComponent::getDamageRoll() const {
 	return m_damageRollData; 
}
Roll CombatComponent::getHitRoll() const {
 	return m_hitRollData;
}
int CombatComponent::getThac0() const {
 	return m_thac0; 
}

bool damage(int damageAmount){
	die();
}






