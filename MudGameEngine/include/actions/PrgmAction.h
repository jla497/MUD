#ifndef PRGMACTION_H
#define PRGMACTION_H

#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The Program Action class defines the behavior for when a admin creates a
 * character
 */
class PrgmAction : public Action {

  public:
    using Action::Action;
    void execute_impl();

  protected:
    std::string description() const override { return u8"Program action"; }
};
#endif