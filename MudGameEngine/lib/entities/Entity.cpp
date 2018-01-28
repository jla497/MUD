#include <string>

#include "Entity.h"

Entity::Entity() {
	//generate entityId
    entityId = nextUniqueId++;
}

unsigned int Entity::getEntityId() {
	return entityId;
}

std::string Entity::getDesc() {
	return desc;
}