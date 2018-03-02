#include <string>
#include <vector>

#include "actions/NullAction.h"

NullAction * NullAction::clone() {
    return new NullAction(*this);
}

void NullAction::execute_impl() {}
