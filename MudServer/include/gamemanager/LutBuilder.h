#ifndef LUTBUILD_H
#define LUTBUILD_H

#include <boost/bimap.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Player.h"
#include "entities/Entity.h"
#include "UniqueId.h"
#include "entities/RoomEntity.h"

namespace mudserver {
namespace gamemanager {

using std::unique_ptr;
using std::unordered_map;
using roomId = unsigned int;

class LutBuilder {
public:

    std::map<roomId, RoomEntity*> createLUT(std::vector<std::unique_ptr<RoomEntity>>& mVector); 

    
};

}  // namespace gamemanager
}  // namespace mudserver
#endif  // GAMESTATE_H
