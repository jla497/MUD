#include "DummyEntity.h"

DummyEntity::DummyEntity(): longdesc(""), shortdesc("") {};
// Sample generic entity, assume properly formatted strings..
DummyEntity::DummyEntity(std::string longdesc, std::string shortdesc)
	: longdesc(longdesc), shortdesc(shortdesc) {
	id = rand();
}

unsigned int DummyEntity::getId() {
	return id;
}

std::string DummyEntity::getLongdesc() {
	return longdesc;
}

std::string DummyEntity::getShortdesc() {
	return shortdesc;
}