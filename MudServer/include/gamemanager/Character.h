#ifndef CHARACTER_H
#define CHARACTER_H

#include <boost/cstdint.hpp>

namespace mudserver {
namespace gamemanager {

using CharacterID = int;

class Character {
    CharacterID id;

public:
    Character(CharacterID id);
    CharacterID getID() const;

};


}  // namespace gamemanager
}  // namespace mudserver
#endif  // CHARACTER_H
