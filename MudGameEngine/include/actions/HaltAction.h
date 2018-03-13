#ifndef HALTACTION_H
#define HALTACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The HaltAction halts the server
 */
class HaltAction : public Action {
  public:
    using Action::Action;
    void execute_impl() override;

  protected:
    std::string description() const override { return u8"Halt action"; }
	std::unique_ptr<Action> clone() const override;
};
#endif // HALTACTION_H