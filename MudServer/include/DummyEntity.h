#ifndef DUMMY_ENTITY_H
#define DUMMY_ENTITY_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include "Entity.h"

class DummyEntity {
    unsigned int id;
    std::string longdesc;
    std::string shortdesc;

public:
    DummyEntity();
	DummyEntity(std::string longdesc, std::string shortdesc);

	unsigned int getId();

	std::string getLongdesc();

	std::string getShortdesc();
};

#endif