#include "UniqueId.h"
unsigned int UniqueId::nextUniqueId = 1;

unsigned int UniqueId::getId() {
    return id;
}