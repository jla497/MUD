#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

#include "Roll.h"
#include "entities/CombatComponent.h"
#include "entities/Entity.h"
#include "entities/ObjectEntity.h"
#include <map>

class CombatComponent;
class CharacterEntity : public Entity {
  private:
    bool isPlayerCharacter = false;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        (void)version;
        ar &m_entityId;
        ar &m_desc;
        ar &m_exp;
        ar &m_gold;
        ar &m_typeId;
        ar &m_keywords;
        ar &m_level;
        ar &m_longDesc;
        ar &m_shortDesc;
        ar &combatComponent;
        ar &m_mana;
    }

    std::vector<std::string> m_desc;
    unsigned int m_exp{};
    int m_gold{};
    unsigned int m_typeId{}; // npcs have types, what to do for players?
    std::vector<std::string> m_keywords;
    unsigned int m_level{};
    std::vector<std::string> m_longDesc;
    std::string m_shortDesc;
    std::map<int, ObjectEntity> m_objects;
    unsigned int m_mana = 100;

    CombatComponent combatComponent;

    // ASSUME: can only level up via experience
    // should calculate level every time exp changed
    void calculateLevel();

  public:
    CharacterEntity() = default;
    CharacterEntity(int armor, std::string damage,
                    std::vector<std::string> desc, unsigned int exp, int gold,
                    std::string hit, unsigned int typeId,
                    std::vector<std::string> keywords, unsigned int level,
                    std::vector<std::string> longDesc, std::string shortDesc,
                    int thac0); // TODO make by reference

    // Getters
    std::vector<std::string> getDesc() const;
    unsigned int getExp() const;
    int getGold() const;
    unsigned int getTypeId() const;
    std::vector<std::string> getKeywords() const;
    unsigned int getLevel() const;
    std::vector<std::string> getLongDesc() const;
    std::string getShortDesc() const;
    unsigned int getMana() const;

    // Setters
    void setShortDesc(std::string name);

    // Combat
    CombatComponent *getCombatComponent();

    // Money
    void addGold(unsigned int amount);
    void subtractGold(unsigned int amount);
    bool hasGold() const;

    // Mana
    void addMana(unsigned int amount);
    void subtractMana(unsigned int amount);

    // Experience
    void incExp(unsigned int expPoints);

    // Objects
    void equipObject(const ObjectEntity &object);
    ObjectEntity getObject(int id);
    std::map<int, ObjectEntity> getObjects();

    void set_isPlayerCharacter();
    bool get_isPlayerCharacter();
};
#endif
