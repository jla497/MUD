#include <string>
#include <utility>
#include <vector>

#include "entities/PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(int armor, std::string damage,
                                 std::vector<std::string> desc,
                                 unsigned int exp, int gold, std::string hit,
                                 std::vector<std::string> keywords,
                                 unsigned int level,
                                 std::vector<std::string> longDesc,
                                 std::string shortDesc, int thac0)
    : CharacterEntity::CharacterEntity(
          armor, std::move(damage), std::move(desc), exp, gold, std::move(hit),
          std::move(keywords), level, std::move(longDesc), std::move(shortDesc),
          thac0) {}
