#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H
#include "Roll.h"
#include "entities/CharacterComponent.h"

enum class CombatStates { NOT_FIGHTING, FIGHTING };

class CombatComponent : public CharacterComponent {
  private:
    int m_armor;
    int m_thac0;
    CombatStates m_combatState;
    Roll m_damageRollData;
    Roll m_hitRollData;
  public:
    CombatComponent(int armor, int thac0,Roll m_damageRollData,Roll m_hitRollData);
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

    // edit combat state
    CombatStates getCombatState() const;
    void engageCombatState();
    void endCombatState();

};
#endif
