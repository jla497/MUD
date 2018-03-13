
#include <memory>
#include <string>
#include <vector>

#include "actions/NullAction.h"

std::unique_ptr<Action> NullAction::clone() const {
	return std::make_unique<NullAction>(*this);
}

void NullAction::execute_impl() {}
