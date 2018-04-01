#include "Spell.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <string>
#include <vector>

Spell::Spell() {
    effect = "";
    mana = 0;
    minlevel = 0;
    name = "";
    duration = -1; // need to signify that if there's no duration, spell will
                   // last (FIXME in future)
    dammsg = "";
    wearoff = "";
    immchar = "";
    damage = "";
}

std::string Spell::getEffect() { return effect; }

unsigned int Spell::getMana() { return mana; }

unsigned int Spell::getMinLevel() { return minlevel; }

std::string Spell::getName() { return name; }

int Spell::getDuration() { return duration; }

Spell::DisplayMessages Spell::getDisplayMessages(std::string casterName,
                                                 std::string victimName,
                                                 std::string victimGender) {
    Spell::DisplayMessages modifiedMessages;
    modifiedMessages.hitchar = formatUserDisplayStrings(
        messages.hitchar, casterName, victimName, victimGender);
    modifiedMessages.hitroom = formatUserDisplayStrings(
        messages.hitroom, casterName, victimName, victimGender);
    modifiedMessages.hitvict = formatUserDisplayStrings(
        messages.hitvict, casterName, victimName, victimGender);
    modifiedMessages.misschar = formatUserDisplayStrings(
        messages.misschar, casterName, victimName, victimGender);
    modifiedMessages.missroom = formatUserDisplayStrings(
        messages.missroom, casterName, victimName, victimGender);
    modifiedMessages.missvict = formatUserDisplayStrings(
        messages.missvict, casterName, victimName, victimGender);
    return modifiedMessages;
}

std::string Spell::getDammsg() { return dammsg; }

std::string Spell::getWearoff() { return wearoff; }

std::string Spell::getImmchar() { return immchar; }

std::string Spell::getDamage() { return damage; }

Spell::SpellType Spell::getType() { return type; }

void Spell::setEffect(const std::string &effect) { this->effect = effect; }

void Spell::setMana(unsigned int mana) { this->mana = mana; }

void Spell::setMinLevel(unsigned int minlevel) { this->minlevel = minlevel; }

void Spell::setName(const std::string &name) { this->name = name; }

void Spell::setDisplayMessages(Spell::DisplayMessages messages) {
    this->messages.hitchar = messages.hitchar;
    this->messages.hitroom = messages.hitroom;
    this->messages.hitvict = messages.hitvict;
    this->messages.missroom = messages.missroom;
    this->messages.misschar = messages.misschar;
    this->messages.missvict = messages.missvict;
}

void Spell::setDuration(int duration) { this->duration = duration; }

void Spell::setDammsg(const std::string &dammsg) { this->dammsg = dammsg; }

void Spell::setWearoff(const std::string &wearoff) { this->wearoff = wearoff; }

void Spell::setImmchar(const std::string &immchar) { this->immchar = immchar; }

void Spell::setDamage(const std::string &damage) { this->damage = damage; }

void Spell::setType(Spell::SpellType type) { this->type = type; }

std::string Spell::formatUserDisplayStrings(const std::string &displayString,
                                            const std::string &casterName,
                                            const std::string &victimName,
                                            const std::string &victimGender) {
    std::string modifiedString = displayString;
    if (casterName.length() > 0) {
        boost::replace_all(modifiedString, "$n", casterName);
    } else {
        boost::replace_all(modifiedString, "$n", "someone");
    }
    if (victimName.length() > 0) {
        boost::replace_all(modifiedString, "$N", victimName);
    } else {
        boost::replace_all(modifiedString, "$N", "someone");
    }
    // FIXME: should replace victim gender with enums
    if (victimGender == "F") {
        boost::replace_all(modifiedString, "$E", "she");
        boost::replace_all(modifiedString, "$M", "her");
        boost::replace_all(modifiedString, "$S", "her");
    } else if (victimGender == "M") {
        boost::replace_all(modifiedString, "$E", "he");
        boost::replace_all(modifiedString, "$M", "him");
        boost::replace_all(modifiedString, "$S", "his");
    } else {
        boost::replace_all(modifiedString, "$E", "it");
        boost::replace_all(modifiedString, "$M", "it");
        boost::replace_all(modifiedString, "$S", "its");
    }
    return modifiedString;
}

size_t Spell::findNthQuoteInEffects(size_t position, size_t nth) {
    if (effect.length() <= position) {
        return std::string::npos;
    }
    size_t found_position = effect.find('\'', position);
    if (nth == 0 || nth == 1 || found_position == std::string::npos) {
        return found_position;
    } else {
        return findNthQuoteInEffects(found_position + 1, nth - 1);
    }
}

std::string Spell::getEffectsFormula() {
    size_t start = findNthQuoteInEffects(0, EFFECT_QUOTE_POSITION);
    size_t end = findNthQuoteInEffects(0, EFFECT_QUOTE_POSITION + 1);
    if (start != std::string::npos && end != std::string::npos) {
        return effect.substr(start + 1, end - start - 1);
    } else {
        return "";
    }
}

int Spell::calculateSpellEffect(unsigned int characterLevel) {
    // check if spell is valid type as well (once dictionary/lookup is
    // implemented)
    if (isCharacterValidLevel(characterLevel)) {
        std::string formula = getEffectsFormula();
        if (formula.length() > 0) {
            //"parse" the formula to calculate
            // suggestion: use exprtk mathematical expressions library to
            // "parse" formula
            return 0; // temporary
        }
    }
    return 0; // temporary
}

int Spell::calculateDamage(unsigned int characterLevel) {
    if (isCharacterValidLevel(characterLevel)) {
        //"parse" formula
        return 0; // temporary
    }
    return 0;
}

bool Spell::isCharacterValidLevel(unsigned int characterLevel) {
    return minlevel <= characterLevel;
}

bool Spell::isEnoughMana(unsigned int characterMana) {
    return mana <= characterMana;
}