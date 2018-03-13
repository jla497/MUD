
#include <memory>
#include <string>
#include <vector>

#include "actions/SaveAction.h"

std::unique_ptr<Action> SaveAction::clone() const {
	return std::make_unique<SaveAction>(*this);
}

void SaveAction::execute_impl() { gameManager.persistData(); }
