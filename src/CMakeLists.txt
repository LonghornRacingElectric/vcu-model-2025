file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.c])
set(SOURCES ${SOURCES}
        ../inc/blocks/AppsProcessor.h
        blocks/AppsProcessor.c
        ../inc/blocks/Stompp.h
        blocks/Stompp.c
        ../inc/util/Lookup1D.h
        util/Lookup1D.c
        ../inc/blocks/TorqueMap.h
        blocks/TorqueMap.c
        ../inc/util/Timer.h
        util/Timer.c
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