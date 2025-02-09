file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES}
        ../inc/util/Debounce.h
        util/Debounce.c
        ../inc/util/LowPassFilter.h
        util/LowPassFilter.c
        ../inc/blocks/TractionControl.h
        blocks/TractionControl.c
        ../inc/blocks/Steering.h
        blocks/Steering.c
        ../inc/blocks/Cooling.h
        blocks/Cooling.c
        ../inc/blocks/Indicator.h
        blocks/Indicator.c)

add_library(vcu_model_lib STATIC ${SOURCES})