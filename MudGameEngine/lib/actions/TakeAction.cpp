#include "actions/TakeAction.h"
#include "logging.h"

// std::unique_ptr<TakeAction> TakeAction::clone() { return std::unique_ptr<TakeAction>(*this); }
TakeAction *TakeAction::clone() { return new TakeAction(*this); }

void TakeAction::execute_impl() {
	static auto logger =
		mudserver::logging::getLogger("Action::TakeAction");

}