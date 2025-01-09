//
// Created by henry on 1/7/2025.
//

#ifndef DEBOUNCE_H
#define DEBOUNCE_H


#include "Timer.h"

class Debounce {
private:
    bool state;
    Timer timer = Timer(0);
public:
    Debounce(float duration, bool initialState);
    void add(bool input, float deltaTime);
    bool get();
};

#endif //DEBOUNCE_H
