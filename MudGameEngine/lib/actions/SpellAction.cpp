
#include <memory>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "actions/SpellAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

std::unique_ptr<Action> SpellAction::clone() const {
    return std::make_unique<SpellAction>(*this);
}
