#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include <map>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

#include "Roll.h"
#include "entities/Entity.h"
#include "entities/ObjectEntity.h"

enum class CombatStates { NOT_FIGHTING, FIGHTING };

class CharacterEntity : public Entity {
  private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & m_entityId;
        ar & m_armor;
        ar & m_desc;
        ar & m_exp;
        ar & m_gold;
        ar & m_typeId;
        ar & m_keywords;
        ar & m_level;
        ar & m_longDesc;
        ar & m_shortDesc;
        ar & m_thac0;
    }

    int m_armor;
    // std::string m_damage; // TODO: string for now
    std::vector<std::string> m_desc;
    unsigned int m_exp;
    int m_gold;
    // std::string m_hit; // TODO: string for now
    unsigned int m_typeId; // npcs have types, what to do for players?
    std::vector<std::string> m_keywords;
    unsigned int m_level{};
    std::vector<std::string> m_longDesc;
    std::string m_shortDesc;
    int m_thac0{};
    std::map<int, ObjectEntity> m_objects;

    CombatStates m_combatState;

    Roll m_damageRollData; // ???
    Roll m_hitRollData;    // ???

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
    Roll getDamage() const;

    std::vector<std::string> getDesc() const;

    unsigned int getExp() const;

    int getGold() const;

    Roll getHit() const;

    unsigned int getTypeId() const;

    std::vector<std::string> getKeywords() const;

    unsigned int getLevel() const;

    std::vector<std::string> getLongDesc() const;

    std::string getShortDesc() const;
    void setShortDesc(std::string name);

    int getThac0() const;

    // Combat related
    CombatStates getCombatState() const;
    void engageCombatState();
    void endCombatState();

    // currently gold is signed but good to have
    // separate methods for adding and subtracting
    // ASSUME: no limit to debt or max money
    void addGold(unsigned int amount);
    void subtractGold(unsigned int amount);
    bool hasGold() const;

    // Experience is unsigned to assume no negative exp
    void incExp(unsigned int expPoints);

    void equipObject(ObjectEntity object);
    ObjectEntity getObject(int id);
    std::map<int, ObjectEntity> getObjects();
};

#endif
