
#include <string>
#include <boost/algorithm/string/find.hpp>
#include "Spell.h"

Spell Spell::Spell() {
	effect = "";
	mana = 0;
	minlevel = 0;
	name = "";
	duration = -1; //need to signify that if there's no duration, spell will last (FIXME in future)
	hitchar = "";
	hitroom = "";
	hitvict = "";
	missroom = "";
	misschar = "";
	dammsg = "";
	wearoff = "";
	immchar = "";
	damage = "";
} 

std::string Spell::getEffect() {
	return effect;
}

int Spell::getMana() {
	return mana;
}

unsigned int Spell::getMinLevel() {
	return minlevel;
}

std::string Spell::getName() {
	return name
}

int Spell::getDuration() {
	return duration;
}

std::string Spell::getHitChar() {
	//use stringf to replace all $x's with character names
	return hitchar;
}

std::string Spell::getHitRoom() {
	return hitroom;
}
		
std::string Spell::getHitVict() {
	return hitvict;
}

std::string Spell::getMissRoom() {
	return missroom;
}

std::string Spell::getMissChar() {
	return misschar;
}
		
std::string Spell::getDammsg() {
	return dammsg;
}
		
std::string Spell::getWearoff() {
	return wearoff;
}
		
std::string Spell::getImmchar() {
	return immchar;
}
		
std::string Spell::getDamage() {
	return damage;
}

void Spell::setEffect(std::string effect) {
	this->effect = effect;
}
		
void Spell::setMana(int mana) {
	this->mana = mana;
}
		
void Spell::setMinLevel(unsigned int minlevel) {
	this->minlevel = minlevel;
}

void Spell::setName(std::string name) {
	this->name = name;
}
		
void Spell::setDuration(int duration) {
	this->duration = duration;
}

void Spell::setHitChar(std::string hitchar) {
	this->hitchar = hitchar;
}

void Spell::setHitRoom(std::string hitroom) {
	this->hitroom = hitroom;
}

void Spell::setHitVict(std::string hitvict) {
	this->hitvict = hitvict;
}

void Spell::setMissRoom(std::string missroom) {
	this->missroom = missroom;
}

void Spell::setMissChar(std::string misschar) {
	this->misschar = misschar;
}

void Spell::setDammsg(std::string dammsg) {
	this->dammsg = dammsg;
}
		
void Spell::setWearoff(std::string wearoff) {
	this->wearoff = wearoff;
}

void Spell::setImmchar(std::string immchar) {
	this->immchar = immchar;
}

void Spell::setDamage(std::string damage) {
	this->damage = damage;
}

size_t Spell::findNthQuoteInEffects(size_t position, size_t nth) {
	if (effect.length() <= position) {
		return string::npos;
	}
	size_t found_position = effect.find("'", position);
	if (1 == nth || string::npos == found_position) {
		return found_position;
	} else {
		return findNthQuoteInEffects(found_position + 1, nth - 1);
	}
}

std::string Spell::getEffectsFormula() {
	size_t start = string::npos;
	size_t end = string::npos;
	start = findNthQuoteInEffects(0, EFFECT_QUOTE_POSITION);
	end = findNthQuoteInEffects(0, EFFECT_QUOTE_POSITION + 1);
	if (start != string::npos && end != string::npos) {
		return effect.substr(start + 1, end - start);
	} else {
		return "";
	}
}

int Spell::calculateSpellEffect(unsigned int characterLevel) {
	//check if spell is valid type as well (once dictionary/lookup is implemented)
	if(isCharacterValidLevel(characterLevel)) {
		std::string formula = getEffectsFormula();
		if (formula.length() > 0) {
			
		}
	}
}

bool Spell::isCharacterValidLevel(unsigned int characterLevel) {
	if (minlevel <= characterLevel) {
		return true;
	} else {
		return false;
	}
}