#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The MoveAction class defines the behavior for when a player character moves
 * from one room to another.
 */
class MoveAction : public Action {
    static std::vector<std::string> moveLookup;

  public:
    using Action::Action;
    void execute_impl();
    MoveAction *clone();

  protected:
    std::string description() const override { return u8"Move action"; }
};
#endif