#include <string>
#include <vector>

#include "entities/CharacterEntity.h"

CharacterEntity::CharacterEntity(int armor, std::string damage,
                    std::vector<std::string> desc, unsigned int exp, int gold,
                    std::string hit, unsigned int typeId, std::vector<std::string> keywords,
                    unsigned int level, std::vector<std::string> longDesc,
                    std::string shortDesc, int thac0)
    : Entity::Entity(), m_armor(armor), /*m_damage(damage),*/ m_desc(desc),
      m_typeId(typeId), m_exp(exp), m_gold(gold), /*m_hit(hit),*/ m_keywords(keywords),
      m_level(level), m_longDesc(longDesc), m_shortDesc(shortDesc),
      m_thac0(thac0), m_combatState(CombatStates::NOT_FIGHTING) {

    // TODO set Roll parameters using hit and damage
    m_damageRollData = {}; // TODO: parse damage string
    m_hitRollData = {}; // TODO: parse hit string
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

bool CharacterEntity::hasGold() { return m_gold > 0 ? true : false; }

void CharacterEntity::incExp(unsigned int expPoints) {
    m_exp += expPoints;
    // calculateLevel();
}
