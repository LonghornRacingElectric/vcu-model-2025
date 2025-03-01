//
// Created by henry on 1/7/2025.
//

#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include "Timer.h"

typedef struct Debounce {
    Timer timer;
    bool state;
} Debounce;

void Debounce_init(Debounce* debounce, float duration, bool initialState);
void Debounce_add(Debounce* debounce, bool input, float deltaTime);
bool Debounce_get(Debounce* debounce);

#endif  // DEBOUNCE_H
