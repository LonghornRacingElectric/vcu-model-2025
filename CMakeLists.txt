cmake_minimum_required(VERSION 3.24)
project(vcu_model)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(inc)

add_subdirectory(tests)
add_subdirectory(src)

file(GLOB SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(vcu_model STATIC ${SRC_FILES})

target_include_directories(vcu_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)



if(DEFINED SIL_TESTING)
    add_subdirectory(sil)
endif()