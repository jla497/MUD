//
// Created by jla497 on 25/03/18.
//
#include "Event.h"

namespace event {
Event::Event()
    : entity(nullptr), type(EventType::undefined), args({}){

                                                   };

Event::Event(CharacterEntity *e, EventType event, std::vector<std::string> a)
    : entity(e), type(event), args(a){};

CharacterEntity *Event::getEntity() { return entity; };

EventType Event::getType() { return type; }
std::vector<std::string> Event::getArgs() { return args; }
}
