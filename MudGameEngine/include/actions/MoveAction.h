#ifndef MOVEACTION_H
#define MOVEACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

// The MoveAction class defines the behavior for when an Player moves from one
// Room to another.
class MoveAction : public Action {
public:
    using Action::Action;
    void execute() override;
protected:
    std::string description() const override { return u8"Move action"; }
};
#endif