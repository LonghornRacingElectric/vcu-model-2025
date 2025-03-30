#include "../../inc/util/Timer.h"

void Timer_init(Timer* timer, float duration) {
    timer->duration = duration;
    timer->time = duration;
}

void Timer_reset(Timer* timer) { timer->time = timer->duration; }

void Timer_count(Timer* timer, float deltaTime) { timer->time -= deltaTime; }

bool Timer_isFinished(Timer* timer) { return timer->time <= 0; }
