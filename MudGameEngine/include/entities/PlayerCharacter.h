#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "CharacterEntity.h"
#include "gamemanager/Administrator.h"

class PlayerCharacter : public CharacterEntity {

    using Administrator = mudserver::gamemanager::Administrator;

  private:
    // Possibly race here later
    Administrator *admin = nullptr;

  public:
    PlayerCharacter() = default;
    PlayerCharacter(int armor, std::string damage,
                    std::vector<std::string> desc, unsigned int exp, int gold,
                    std::string hit, std::vector<std::string> keywords,
                    unsigned int level, std::vector<std::string> longDesc,
                    std::string shortDesc, int thac0);
    void getAdminPrivileges();
    Administrator *getAdministrator();
};

#endif
