/*

Library to run timers based on delta times passed into the model

*/

#ifndef VCU_CORE_TIMER_H
#define VCU_CORE_TIMER_H

#include <stdbool.h>

typedef struct Timer {
    float duration;
    float time;
} Timer;

void Timer_init(Timer *timer, float duration);
void Timer_reset(Timer *timer);
void Timer_count(Timer *timer, float deltaTime);
bool Timer_isFinished(Timer *timer);

#endif  // VCU_CORE_TIMER_H