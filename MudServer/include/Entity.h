#ifndef ENTITY_H
#define ENTITY_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>

/*Entity Interface for making other types of entities like:
  players, rooms, objects*/
class Entity {
    // unsigned int id;
    // std::string desc;

    // what were buffers in entities for?
    // std::string inBuffer;
    // std::string outBuffer;
public:
	// Entity();

	virtual unsigned int getId() = 0;

	virtual std::string getDesc() = 0;
};

#endif