//
// Created by jla497 on 24/03/18.
//

#ifndef ADVENTURE2018_EVENT_H
#define ADVENTURE2018_EVENT_H

#include "entities/CharacterEntity.h"
#include <vector>

namespace event {
enum class EventType {
    undefined = 0,
    died_self,
    startcombat,
    endcombat,
    say,
    interact,
    alone
};

class Event {
    CharacterEntity *entity = nullptr;
    EventType type = EventType::undefined;
    std::vector<std::string> args{};

  public:
    Event();
    Event(CharacterEntity *e, EventType event, std::vector<std::string> a);
    CharacterEntity *getEntity();
    EventType getType();
    std::vector<std::string> getArgs();

    friend bool operator<(Event const &a, Event const &b) {
        return a.type < b.type;
    }
};
} // namespace event
#endif // ADVENTURE2018_EVENT_H
