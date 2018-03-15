//
// Created by jla497 on 01/03/18.
//

#include <memory>

#include "actions/TimedAction.h"
#include "logging.h"

// namespace actmess = mudserver::resources::actions;

void TimedAction::execute_impl() {
    if (timeRemaining == -1) {
        timeRemaining = 20;
    }
    static auto logger = mudserver::logging::getLogger("TimedAction::execute");
    logger->debug("kick yourself");
}

std::unique_ptr<Action> TimedAction::clone() const {
    return std::make_unique<TimedAction>(*this);
}
