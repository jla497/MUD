
#include <memory>
#include <string>
#include <vector>

#include "actions/HaltAction.h"

std::unique_ptr<Action> HaltAction::clone() const {
    return std::make_unique<HaltAction>(*this);
}

void HaltAction::execute_impl() {
    gameManager->persistData();
    gameManager->haltServer();
}
