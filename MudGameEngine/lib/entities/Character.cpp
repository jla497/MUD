#include <string>
#include <vector>

#include "entities/Character.h"

Character::Character(int armor, std::string& damage,
                     std::vector<std::string>& desc, unsigned int exp, int gold,
                     std::string& hit,
                     std::vector<std::string>& keywords, unsigned int level,
                     std::vector<std::string>& longDesc, std::string& shortDesc,
                     int thac0)

    : Entity::Entity(),
      m_armor(armor),
      m_damage(damage),
      m_desc(desc),
      m_exp(exp),
      m_gold(gold),
      m_hit(hit),
      m_keywords(keywords),
      m_level(level),
      m_longDesc(longDesc),
      m_shortDesc(shortDesc),
      m_thac0(thac0),
      m_combatState(CombatStates::NOT_FIGHTING) {

    // TODO set Roll parameters using hit and damage
}

std::string Character::getDamage() const {
   return m_damage;
}

std::vector<std::string> Character::getDesc() const {
   return m_desc;
}

unsigned int Character::getExp() const {
   return m_exp;
}

int Character::getGold() const {
   return m_gold;
}

std::string Character::Character::getHit() const {
   return m_hit;
}

std::vector<std::string> Character::Character::getKeywords() const {
   return m_keywords;
}

unsigned int Character::Character::getLevel() const {
   return m_level;
}

std::vector<std::string> Character::Character::getLongDesc() const {
   return m_longDesc;
}

std::string Character::Character::getShortDesc() const {
   return m_shortDesc;
}

int Character::Character::getThac0() const {
   return m_thac0;
}

CombatStates Character::getCombatState() const {
   return m_combatState;
}
void Character::engageCombatState() {
   m_combatState = CombatStates::FIGHTING;
}
void Character::endCombatState() {
   m_combatState = CombatStates::NOT_FIGHTING;
}

void Character::addGold(unsigned int amount) {   
   m_gold += amount;
}

void Character::subtractGold(unsigned int amount) {
   m_gold -= amount;   
}

bool Character::hasGold() {
   return m_gold >0 ? true : false;
}

void Character::incExp(unsigned int expPoints) {
   m_exp += expPoints;
   Character::calculateLevel();
}

