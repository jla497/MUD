#include <string>
#include <vector>

#include "entities/NonPlayerCharacter.h"

NonPlayerCharacter::NonPlayerCharacter(int armor, std::string& damage,
                     std::vector<std::string>& desc, unsigned int exp, int gold,
                     std::string& hit, unsigned int npcTypeId,
                     std::vector<std::string>& keywords, unsigned int level,
                     std::vector<std::string>& longDesc, std::string& shortDesc,
                     int thac0)

    : Character::Character(armor, damage, desc, exp, gold,
         hit, keywords, level, longDesc,
         shortDesc, thac0),
      m_npcTypeId(npcTypeId) {}

unsigned int NonPlayerCharacter::getNpcTypeId() const {
	return m_npcTypeId;
}
