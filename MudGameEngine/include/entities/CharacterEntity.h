#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include "Entity.h"
#include "Roll.h"

enum class CombatStates { NOT_FIGHTING, FIGHTING };

class CharacterEntity : public Entity {
  private:
    int m_armor{};
    std::string m_damage; // TODO: string for now
    std::vector<std::string> m_desc;
    unsigned int m_exp{};
    int m_gold{};
    std::string m_hit; // TODO: string for now
    std::vector<std::string> m_keywords;
    unsigned int m_level{};
    std::vector<std::string> m_longDesc;
    std::string m_shortDesc;
    int m_thac0{};

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
                    std::string hit, std::vector<std::string> keywords,
                    unsigned int level, std::vector<std::string> longDesc,
                    std::string shortDesc, int thac0);

    // Getters
    std::string getDamage() const;

    std::vector<std::string> getDesc() const;

    unsigned int getExp() const;

    int getGold() const;

    std::string getHit() const;

    std::vector<std::string> getKeywords() const;

    unsigned int getLevel() const;

    std::vector<std::string> getLongDesc() const;

    std::string getShortDesc() const;

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
};

#endif
