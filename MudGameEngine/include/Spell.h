#ifndef SPELL_H
#define SPELL_H

class Spell {
	private:
		std::string effect;
		int mana;
		unsigned int minlevel;
		std::string name;
		int duration;
		std::string hitchar;
		std::string hitroom;
		std::string hitvict;
		std::string missroom;
		std::string misschar;
		std::string dammsg;
		std::string wearoff;
		std::string immchar:
		std::string damage;

		//this finds the substring that starts directly after the Nth quote character (') in the string
		//Returns an empty string if quote number is invalid or if there is no characters in between the Nth and N+1 quote
		std::string getEffectsFormula();

	public:
		Spell() = default;

		//getters
		std::string getEffect();
		int getMana();
		unsigned int getMinLevel();
		std::string getName();
		int getDuration();
		std::string getHitChar();
		std::string getHitRoom(std::string characterName);
		std::string getHitVict();
		std::string getMissRoom(std::string characterName);
		std::string getMissChar();
		std::string getDammsg();
		std::string getWearoff();
		std::string getImmchar();
		std::string getDamage();

		//setters
		void setEffect(std::string effect);
		void setMana(int mana);
		void setMinLevel(unsigned int minlevel);
		void setName(std::string name);
		void setDuration(int duration);
		void setHitChar(std::string hitchar);
		void setHitRoom(std::string hitroom);
		void setHitVict(std::string hitvict);
		void setMissRoom(std::string missroom);
		void setMissChar(std::string misschar);
		void setDammsg(std::string dammsg);
		void setWearoff(std::string wearoff);
		void setImmchar(std::string immchar);
		void setDamage(std::string damage);

		//calculates the amount of damage or healing the spell will perform 
		//Rolls a dice, the result may not always be the same!)
		int calculateSpellEffect(unsigned int characterLevel);

		//calculates damage on victim
		int calculateDamage(unsigned int characterLevel);

		//returns true if character is above the minimum level to use the spell
		bool isCharacterValidLevel(unsigned int characterLevel);

		//returns true if character has enough mana to perform spell
		bool isEnoughMana(int characterMana);
}

#endif