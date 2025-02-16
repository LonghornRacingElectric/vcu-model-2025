#ifndef VCU_CORE_TIMER_H
#define VCU_CORE_TIMER_H

#include <stdbool.h>

// class Timer {
// private:
//     float duration;
// public:
//     float time;
//     explicit Timer(float duration);
//     void reset();
//     void count(float deltaTime);
//     bool isFinished();
// };

typedef struct Timer {
        float duration;
        float time;
} Timer;

#ifdef __cplusplus
extern "C" {
#endif
        void Timer_init(Timer *timer, float duration);
        void Timer_reset(Timer *timer);
        void Timer_count(Timer *timer, float deltaTime);
        bool Timer_isFinished(Timer *timer);

#ifdef __cplusplus
}
#endif

#endif //VCU_CORE_TIMER_H