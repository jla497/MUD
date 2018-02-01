#include "gamemanager/Character.h"

namespace mudserver {
namespace gamemanager {

Character::Character() {

}

CharacterID Character::getID() const {
    return id;
}

}  // namespace gamemanager
}  // namespace mudserver
