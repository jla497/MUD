#include "UniqueId.h"

unsigned int UniqueId::nextUniqueId = 1;

bool UniqueId::operator==(const UniqueId& rhs) {
	return this->id == rhs.id;
}
