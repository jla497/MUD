#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "CharacterEntity.h"
#include "gamemanager/Administrator.h"

class PlayerCharacter : public CharacterEntity {
  private:
    // Possibly race here later
    std::unique_ptr<Administrator> admin;
  public:
    PlayerCharacter() = default;
    PlayerCharacter(int armor, std::string damage,
                    std::vector<std::string> desc, unsigned int exp, int gold,
                    std::string hit, std::vector<std::string> keywords,
                    unsigned int level, std::vector<std::string> longDesc,
                    std::string shortDesc, int thac0);
    void getAdminPrivileges();
};

#endif
