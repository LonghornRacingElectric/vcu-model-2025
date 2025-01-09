file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES}
        ../inc/blocks/Prndl.h
        ../inc/util/Debounce.h
        util/Debounce.cpp
        blocks/Prndl.cpp
        ../inc/util/LowPassFilter.h
        util/LowPassFilter.cpp
        ../inc/blocks/TractionControl.h
        blocks/TractionControl.cpp
        ../inc/blocks/Steering.h
        blocks/Steering.cpp
        ../inc/blocks/Cooling.h
        blocks/Cooling.cpp)

add_library(vcu_model_lib STATIC ${SOURCES})