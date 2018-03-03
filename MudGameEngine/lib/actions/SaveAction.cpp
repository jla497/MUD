#include <string>
#include <vector>

#include "actions/SaveAction.h"

void SaveAction::execute_impl() {
    gameManager.persistData();
}
