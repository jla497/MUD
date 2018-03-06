#include <string>
#include <vector>

#include "actions/HaltAction.h"

HaltAction *HaltAction::clone() { return new HaltAction(*this); }

void HaltAction::execute_impl() {
    gameManager.persistData();
    gameManager.haltServer();
}
