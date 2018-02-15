#include <string>
#include <utility>
#include <vector>

#include "entities/CharacterEntity.h"

CharacterEntity::CharacterEntity(int armor, std::string damage,
                     std::vector<std::string> desc, unsigned int exp, int gold,
                     std::string hit,
                     std::vector<std::string> keywords, unsigned int level,
                     std::vector<std::string> longDesc, std::string shortDesc,
                     int thac0)
    : Entity::Entity(),
      m_armor(armor),
      m_damage(std::move(damage)),
      m_desc(std::move(desc)),
      m_exp(exp),
      m_gold(gold),
      m_hit(std::move(hit)),
      m_keywords(std::move(keywords)),
      m_level(level),
      m_longDesc(std::move(longDesc)),
      m_shortDesc(std::move(shortDesc)),
      m_thac0(thac0),
      m_combatState(CombatStates::NOT_FIGHTING) {

    // TODO set Roll parameters using hit and damage
}

std::string CharacterEntity::getDamage() const {
   return m_damage;
}

std::vector<std::string> CharacterEntity::getDesc() const {
   return m_desc;
}

unsigned int CharacterEntity::getExp() const {
   return m_exp;
}

int CharacterEntity::getGold() const {
   return m_gold;
}

std::string CharacterEntity::CharacterEntity::getHit() const {
   return m_hit;
}

std::vector<std::string> CharacterEntity::CharacterEntity::getKeywords() const {
   return m_keywords;
}

unsigned int CharacterEntity::CharacterEntity::getLevel() const {
   return m_level;
}

std::vector<std::string> CharacterEntity::CharacterEntity::getLongDesc() const {
   return m_longDesc;
}

std::string CharacterEntity::CharacterEntity::getShortDesc() const {
   return m_shortDesc;
}

int CharacterEntity::CharacterEntity::getThac0() const {
   return m_thac0;
}

CombatStates CharacterEntity::getCombatState() const {
   return m_combatState;
}
void CharacterEntity::engageCombatState() {
   m_combatState = CombatStates::FIGHTING;
}
void CharacterEntity::endCombatState() {
   m_combatState = CombatStates::NOT_FIGHTING;
}

void CharacterEntity::addGold(unsigned int amount) {
   m_gold += amount;
}

void CharacterEntity::subtractGold(unsigned int amount) {
   m_gold -= amount;   
}

bool CharacterEntity::hasGold() const {
   return m_gold > 0;
}

void CharacterEntity::incExp(unsigned int expPoints) {
   m_exp += expPoints;
   // calculateLevel();
}

