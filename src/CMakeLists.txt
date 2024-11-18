file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})

add_library(vcu_model_lib STATIC ${SOURCES})