#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H

#include <boost/serialization/access.hpp>
#include <string>

#include "Roll.h"
#include "entities/CharacterComponent.h"

enum class CombatStates { NOT_FIGHTING, FIGHTING };

class CombatComponent : public CharacterComponent {
  private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        (void)version;
        ar &maxHealth;
        ar &maxHealth;
        ar &currentHealth;
        ar &armor;
        ar &thac0;
        ar &combatState;
        ar &damageRoll;
        ar &maxHitPointRoll;
    }

    int maxHealth;
    int currentHealth;
    int armor;
    int thac0;
    CombatStates combatState;
    // The Roll use to calculate damage dealt.
    Roll damageRoll;
    Roll maxHitPointRoll;
    std::string enemiesName;
    std::string ownersName;

  public:
    CombatComponent(int armor, int thac0, Roll damageRoll,
                    Roll maxHitPointRoll);
    CombatComponent();
    void setArmor(int armor);
    void setThac0(int thac0);
    void setEnemiesName(std::string enemiesName);
    void setOwnersName(std::string ownersName);

    void setDamageRoll(Roll damageRoll);
    void setHitRoll(Roll maxHitPointRoll);

    int getArmor() const;
    int getThac0() const;
    std::string getEnemiesName() const;
    std::string getOwnersName() const;

    Roll getDamageRoll() const;
    Roll getHitRoll() const;
    std::string getHealthDescription() const;

    // view and change combat state methods
    CombatStates getCombatState() const;
    void engageCombatState();
    void endCombatState();

    void prepareToAttack();
    /*Damage the Character and return true if the character was killed */
    void damage(int damageAmount);
    void heal(int healAmount);
    bool isCharacterDead();
};
#endif
