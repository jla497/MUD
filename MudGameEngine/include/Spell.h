#ifndef SPELL_H
#define SPELL_H

#include <string>

class Spell {
  public:
    enum class SpellType {
        defense,
        offense,
        object,
        personal,
        swap,
        decoy,
        other
    };

    struct DisplayMessages {
        std::string hitchar = "";
        std::string hitroom = "";
        std::string hitvict = "";
        std::string missroom = "";
        std::string misschar = "";
        std::string missvict = "";
    };

    Spell();

    // getters
    std::string getEffect();
    unsigned int getMana();
    unsigned int getMinLevel();
    std::string getName();
    int getDuration();

    // returns the display messages with correctly formatted strings
    DisplayMessages getDisplayMessages(std::string casterName,
                                       std::string victimName,
                                       std::string victimGender);

    std::string getDammsg();
    std::string getWearoff();
    std::string getImmchar();
    std::string getDamage();
    Spell::SpellType getType();

    // setters
    void setEffect(const std::string &effect);
    void setMana(unsigned int mana);
    void setMinLevel(unsigned int minlevel);
    void setName(const std::string &name);
    void setDuration(int duration);
    void setDisplayMessages(DisplayMessages messages);
    void setDammsg(const std::string &dammsg);
    void setWearoff(const std::string &wearoff);
    void setImmchar(const std::string &immchar);
    void setDamage(const std::string &damage);
    void setType(Spell::SpellType type);

    // calculates the amount of damage or healing the spell will perform
    // Rolls a dice, the result may not always be the same!)
    int calculateSpellEffect(unsigned int characterLevel);

    // calculates damage on victim
    int calculateDamage(unsigned int characterLevel);

    // returns true if character is above the minimum level to use the spell
    bool isCharacterValidLevel(unsigned int characterLevel);

    // returns true if character has enough mana to perform spell
    bool isEnoughMana(unsigned int characterMana);

  private:
    std::string effect;
    unsigned int mana{};
    unsigned int minlevel{};
    std::string name;
    int duration{};
    std::string dammsg;
    std::string wearoff;
    std::string immchar;
    std::string damage;
    DisplayMessages messages;
    Spell::SpellType type = SpellType::other;

    static const int EFFECT_QUOTE_POSITION =
        7; // the quote position that precedes the heal/damage formula in effect

    // replaces string formatting specification symbols with character
    // information to display to player
    std::string formatUserDisplayStrings(const std::string &displayString,
                                         const std::string &casterName,
                                         const std::string &victimName,
                                         const std::string &victimGender);

    // finds the substring in the third column of Effect that contains formula
    // for heal/damage
    std::string getEffectsFormula();

    // helper function for getEffectsformula()
    size_t findNthQuoteInEffects(size_t position, size_t nth);
};

#endif