#ifndef CHARACTER_H
#define CHARACTER_H

#include <boost/cstdint.hpp>

namespace mudserver {
namespace gamemanager {

using CharacterID = uintptr_t;

class Character {
    CharacterID id;

public:
    Character();
    CharacterID getID() const;

};


}  // namespace gamemanager
}  // namespace mudserver
#endif  // CHARACTER_H
