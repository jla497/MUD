#ifndef CHARACTER_H
#define CHARACTER_H

#include <boost/cstdint.hpp>

namespace mudserver {
namespace gamemanager {

using CharacterID = uintptr_t;

class Character {

public:
    Character();
    CharacterID getID() const;
private:
    CharacterID id;
};


}  // namespace gamemanager
}  // namespace mudserver
#endif  // CHARACTER_H
