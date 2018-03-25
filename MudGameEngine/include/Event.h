//
// Created by jla497 on 24/03/18.
//

#ifndef ADVENTURE2018_EVENT_H
#define ADVENTURE2018_EVENT_H
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
    public:
        CharacterEntity* entity = nullptr;
        EventType type = EventType::undefined;
        std::vector<std::string> args{};
        friend bool operator< (Event const& a, Event const&b) {
            return a.type < b.type;
        }
    };
}
#endif //ADVENTURE2018_EVENT_H
