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

    SwapAction() = default;

    void execute_impl() override;
    std::unique_ptr<Action> clone() const override;

  protected:
    std::string description() const override { return u8"Swap action"; }
    const int MAX_SWAP_TICKS = 20;
    UniqueId casterId;
    UniqueId targetId;
};
#endif