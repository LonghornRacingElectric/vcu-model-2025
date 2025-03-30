file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.c)
set(SOURCES ${SOURCES})

add_library(vcu_model_lib STATIC ${SOURCES})