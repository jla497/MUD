#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include <map>
#include "Roll.h"
#include "entities/Entity.h"
#include "entities/ObjectEntity.h"
#include "entities/CombatComponent.h"

class CombatComponent;
class CharacterEntity : public Entity {
  private:
    bool isPlayerCharacter = false;
    std::vector<std::string> m_desc;
    unsigned int m_exp;
    int m_gold;
    unsigned int m_typeId; // npcs have types, what to do for players?
    std::vector<std::string> m_keywords;
    unsigned int m_level{};
    std::vector<std::string> m_longDesc;
    std::string m_shortDesc;
    std::map<int, ObjectEntity> m_objects;
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
    CombatComponent* getCombatComponent();

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
