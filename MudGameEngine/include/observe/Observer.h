//
// Created by jla497 on 25/03/18.
//

#ifndef ADVENTURE2018_OBSERVER_H
#define ADVENTURE2018_OBSERVER_H
#include "Event.h"
template <typename T>
class Observer{
public:
    virtual void receiveEvent(T* source) = 0;
};
#endif //ADVENTURE2018_OBSERVER_H
