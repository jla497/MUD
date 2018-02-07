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
        ar &m_maxHealth;
        ar &m_maxHealth;
        ar &m_currentHealth;
        ar &m_armor;
        ar &m_thac0;
        ar &m_combatState;
        ar &m_damageRollData;
        ar &m_hitRollData;
    }

    int m_maxHealth;
    int m_currentHealth;
    int m_armor;
    int m_thac0;
    CombatStates m_combatState;
    // The Roll use to calculate damage dealt.
    Roll m_damageRollData;
    // the Roll used to calculate damage mitigated(my assumption, double check)
    Roll m_hitRollData;
    //TODO: CombatAbilities class
    // CombatAbility combatAbility = nullptr;

  public:
    CombatComponent(int armor, int thac0, Roll m_damageRollData,
                    Roll m_hitRollData);
    CombatComponent();
    CombatStates getCombatState();
    void setArmor(int armor);
    void setThac0(int thac0);
    void setDamageRoll(Roll damageRollData);
    void setHitRoll(Roll hitRollData);
    int getArmor() const;
    int getThac0() const;
    Roll getDamageRoll() const;
    Roll getHitRoll() const;
    std::string getHealthDescription() const;

    // view and change combat state methods
    CombatStates getCombatState() const;
    void engageCombatState();
    void endCombatState();

    //TODO: redesigned/implement
    void prepareToAttack();
    // void prepareToUseCombatAbility(CombatAbility& combatAbility);

    /*Damage the Character and return true if the character was killed */
    bool damage(int damageAmount);
    void heal(int healAmount);
};
#endif
