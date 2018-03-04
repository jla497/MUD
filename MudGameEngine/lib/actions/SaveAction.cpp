#include <string>
#include <vector>

#include "actions/SaveAction.h"

SaveAction *SaveAction::clone() { return new SaveAction(*this); }

void SaveAction::execute_impl() { gameManager.persistData(); }
