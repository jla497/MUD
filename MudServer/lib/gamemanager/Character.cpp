#include "gamemanager/Character.h"

namespace mudserver {
namespace gamemanager {

Character::Character() {}

Character::Character(CharacterID id) :
    id{id} {}

CharacterID Character::getID() const {
    return id;
}

}  // namespace gamemanager
}  // namespace mudserver
