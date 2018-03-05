#ifndef SWAPACTION_H
#define SWAPACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The SwapAction class defines the behavior for when a player character
 * attacks a creature or other character.
 */
class SwapAction : public Action {
public:
    using Action::Action;
    void execute_impl() override;
    SwapAction *clone() override;

protected:
    std::string description() const override { return u8"Swap action"; }
    const int MAX_SWAP_TICKS = 20;
    UniqueId casterId;
    UniqueId targetId;

};
#endif