#include <string>
#include <utility>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "entities/CharacterEntity.h"

CharacterEntity::CharacterEntity(int armor, std::string damage,
                                 std::vector<std::string> desc,
                                 unsigned int exp, int gold, std::string hit,
                                 unsigned int typeId, 
                                 std::vector<std::string> keywords,
                                 unsigned int level,
                                 std::vector<std::string> longDesc,
                                 std::string shortDesc, int thac0)
    : Entity::Entity(), m_armor(armor), /*m_damage(std::move(damage)),*/
      m_desc(std::move(desc)), m_typeId(typeId), m_exp(exp), m_gold(gold), 
      /*m_hit(std::move(hit)),*/
      m_keywords(std::move(keywords)), m_level(level),
      m_longDesc(std::move(longDesc)), m_shortDesc(std::move(shortDesc)),
      m_thac0(thac0), m_combatState(CombatStates::NOT_FIGHTING) {

    std::vector<std::string> tmpHit;
    boost::split(tmpHit, hit, boost::is_any_of("+d"));
    m_hitRollData = {std::stoi(tmpHit.at(0)), std::stoi(tmpHit.at(1)),
                     tmpHit.size() > 2 ? std::stoi(tmpHit.at(2)) : 0};

    std::vector<std::string> tmpDamage;
    boost::split(tmpDamage, damage, boost::is_any_of("+d"));
    m_damageRollData = {std::stoi(tmpDamage.at(0)), std::stoi(tmpDamage.at(1)),
                        tmpDamage.size() > 2 ? std::stoi(tmpDamage.at(2)) : 0};
}

Roll CharacterEntity::getDamage() const { return m_damageRollData; }

std::vector<std::string> CharacterEntity::getDesc() const { return m_desc; }

unsigned int CharacterEntity::getExp() const { return m_exp; }

int CharacterEntity::getGold() const { return m_gold; }

Roll CharacterEntity::getHit() const { return m_hitRollData; }

unsigned int CharacterEntity::getTypeId() const { return m_typeId; }

std::vector<std::string> CharacterEntity::getKeywords() const {
    return m_keywords;
}

unsigned int CharacterEntity::getLevel() const {
    return m_level;
}

std::vector<std::string> CharacterEntity::getLongDesc() const {
    return m_longDesc;
}

std::string CharacterEntity::getShortDesc() const {
    return m_shortDesc;
}

int CharacterEntity::getThac0() const { return m_thac0; }

CombatStates CharacterEntity::getCombatState() const { return m_combatState; }
void CharacterEntity::engageCombatState() {
    m_combatState = CombatStates::FIGHTING;
}
void CharacterEntity::endCombatState() {
    m_combatState = CombatStates::NOT_FIGHTING;
}

void CharacterEntity::addGold(unsigned int amount) { m_gold += amount; }

void CharacterEntity::subtractGold(unsigned int amount) { m_gold -= amount; }

bool CharacterEntity::hasGold() const { return m_gold > 0; }

void CharacterEntity::incExp(unsigned int expPoints) {
    m_exp += expPoints;
    // calculateLevel();
}
