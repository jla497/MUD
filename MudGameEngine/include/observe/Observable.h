//
// Created by jla497 on 25/03/18.
//

#ifndef ADVENTURE2018_OBSERVABLE_H
#define ADVENTURE2018_OBSERVABLE_H

#include "Observer.h"

template <typename T>
class Observable{
    Observer<T>* observer;
public:
    void notify(T* source) {
        observer->receiveEvent(source);
    }

    void subscribe(Observer<T>* o){
        observer = o;
    }
};
#endif //ADVENTURE2018_OBSERVABLE_H
