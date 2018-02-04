#include "UniqueId.h"

UniqueId::UniqueId() : id(nextUniqueId++) {}

unsigned int UniqueId::getUniqueId() (
	return id;
);