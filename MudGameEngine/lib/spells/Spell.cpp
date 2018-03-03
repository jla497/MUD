
#include <string>
#include "Spell.h"

Spell Spell() {
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

std::string getEffect() {
	return effect;
}

int getMana() {
	return mana;
}

unsigned int getMinLevel() {
	return minlevel;
}

std::string getName() {
	return name
}

int getDuration() {
	return duration;
}

std::string getHitChar() {
	//use stringf to replace all $x's with character names
	return hitchar;
}

std::string getHitRoom() {
	return hitroom;
}
		
std::string getHitVict() {
	return hitvict;
}

std::string getMissRoom() {
	return missroom;
}

std::string getMissChar() {
	return misschar;
}
		
std::string getDammsg() {
	return dammsg;
}
		
std::string getWearoff() {
	return wearoff;
}
		
std::string getImmchar() {
	return immchar;
}
		
std::string getDamage() {
	return damage;
}

void setEffect(std::string effect) {
	this->effect = effect;
}
		
void setMana(int mana) {
	this->mana = mana;
}
		
void setMinLevel(unsigned int minlevel) {
	this->minlevel = minlevel;
}

void setName(std::string name) {
	this->name = name;
}
		
void setDuration(int duration) {
	this->duration = duration;
}

void setHitChar(std::string hitchar) {
	this->hitchar = hitchar;
}

void setHitRoom(std::string hitroom) {
	this->hitroom = hitroom;
}

void setHitVict(std::string hitvict) {
	this->hitvict = hitvict;
}

void setMissRoom(std::string missroom) {
	this->missroom = missroom;
}

void setMissChar(std::string misschar) {
	this->misschar = misschar;
}

void setDammsg(std::string dammsg) {
	this->dammsg = dammsg;
}
		
void setWearoff(std::string wearoff) {
	this->wearoff = wearoff;
}

void setImmchar(std::string immchar) {
	this->immchar = immchar;
}

void setDamage(std::string damage) {
	this->damage = damage;
}

		//calculates the amount of damage or healing the spell will perform 
		//Rolls a dice, the result may not always be the same!)
int calculateSpellEffect(unsigned int characterLevel) {
	
}

//returns true if character is above the minimum level to use the spell
bool isCharacterValidLevel(unsigned int characterLevel) {
	if (minlevel <= characterLevel) {
		return true;
	} else {
		return false;
	}
}