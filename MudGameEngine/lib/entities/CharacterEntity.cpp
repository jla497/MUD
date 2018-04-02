#include <boost/algorithm/string.hpp>
#include <string>
#include <utility>
#include <vector>

#include "entities/CharacterEntity.h"
#include "entities/CombatComponent.h"
#include "entities/ObjectEntity.h"

CharacterEntity::CharacterEntity(
    int armor, std::string damage, std::vector<std::string> desc,
    unsigned int exp, int gold, std::string hit, unsigned int typeId,
    std::vector<std::string> keywords, unsigned int level,
    std::vector<std::string> longDesc, std::string shortDesc, int thac0)
    : Entity::Entity(), m_desc(std::move(desc)), m_exp(exp), m_gold(gold),
      m_typeId(typeId), m_keywords(std::move(keywords)), m_level(level),
      m_longDesc(std::move(longDesc)), m_shortDesc(std::move(shortDesc)) {

    std::vector<std::string> tmpHit;
    boost::split(tmpHit, hit, boost::is_any_of("+d"));
    Roll m_hitRollData = {std::stoi(tmpHit.at(0)), std::stoi(tmpHit.at(1)),
                          tmpHit.size() > 2 ? std::stoi(tmpHit.at(2)) : 0};

    std::vector<std::string> tmpDamage;
    boost::split(tmpDamage, damage, boost::is_any_of("+d"));
    Roll m_damageRollData = {
        std::stoi(tmpDamage.at(0)), std::stoi(tmpDamage.at(1)),
        tmpDamage.size() > 2 ? std::stoi(tmpDamage.at(2)) : 0};

    // TODO: Moving out roll parsing to before calling the constructer
    // so we can init the combat Component along with the other fields
    // init combat Component
    this->combatComponent.setArmor(armor);
    this->combatComponent.setThac0(thac0);
    this->combatComponent.setDamageRoll(m_damageRollData);
    this->combatComponent.setHitRoll(m_hitRollData);
    this->combatComponent.setOwnersName(m_shortDesc);
}

std::vector<std::string> CharacterEntity::getDesc() const { return m_desc; }
unsigned int CharacterEntity::getExp() const { return m_exp; }
int CharacterEntity::getGold() const { return m_gold; }
unsigned int CharacterEntity::getTypeId() const { return m_typeId; }

std::vector<std::string> CharacterEntity::getKeywords() const {
    return m_keywords;
}

unsigned int CharacterEntity::getLevel() const { return m_level; }

std::vector<std::string> CharacterEntity::getLongDesc() const {
    return m_longDesc;
}

std::string CharacterEntity::getShortDesc() const { return m_shortDesc; }

unsigned int CharacterEntity::getMana() const { return m_mana; }

void CharacterEntity::addGold(unsigned int amount) { m_gold += amount; }

void CharacterEntity::subtractGold(unsigned int amount) { m_gold -= amount; }

void CharacterEntity::addMana(unsigned int amount) { m_mana += amount; }

void CharacterEntity::subtractMana(unsigned int amount) { m_mana -= amount; }

bool CharacterEntity::hasGold() const { return m_gold > 0; }

void CharacterEntity::incExp(unsigned int expPoints) {
    m_exp += expPoints;
    calculateLevel();
}
void CharacterEntity::calculateLevel() {
    // Ask for specs
}
void CharacterEntity::equipObject(const ObjectEntity &object) {
    m_objects[object.getObjectTypeId()] = object;
}
ObjectEntity CharacterEntity::getObject(int id) {
    auto objectItr = m_objects.find(id);
    if (objectItr != m_objects.end()) {
        auto object = objectItr->second;
        m_objects.erase(objectItr);
        return object;
    } else {
        throw "no such object found";
    }
}

std::map<int, ObjectEntity> CharacterEntity::getObjects() { return m_objects; }

void CharacterEntity::setShortDesc(std::string name) {
    m_shortDesc = std::move(name);
};

CombatComponent *CharacterEntity::getCombatComponent() {
    return &combatComponent;
}

void CharacterEntity::set_isPlayerCharacter() { isPlayerCharacter = true; }
bool CharacterEntity::get_isPlayerCharacter() { return isPlayerCharacter; }