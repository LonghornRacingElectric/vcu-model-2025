//
// Created by henry on 1/7/2025.
//

#include "../../inc/util/Debounce.h"

void Debounce_init(Debounce* debounce, float duration, bool initialState) {
    //debounce->timer = Timer(duration);
    Timer_init(&debounce->timer, duration);
    debounce->state = initialState;
}

void Debounce_add(Debounce* debounce, bool input, float deltaTime) {
    if(debounce->state != input) {
        //debounce->timer.count(deltaTime);
        Timer_count(&debounce->timer, deltaTime);
        if(Timer_isFinished(&debounce->timer)) {
            Timer_reset(&debounce->timer);
            debounce->state = input;
        }
    } else {
        Timer_reset(&debounce->timer);
        //timer.reset();
    }
}

bool Debounce_get(Debounce* debounce) {
    return debounce->state;
}
