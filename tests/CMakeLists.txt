set(BINARY vcu_model_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.cpp)

enable_testing()

add_executable(
        ${BINARY}
        ${TEST_SOURCES}
        AppsProcessorTests.cpp
        StomppTests.cpp
        TorqueMapTests.cpp
)

target_link_libraries(
        ${BINARY}
        GTest::gtest_main
        vcu_model_lib
)

include(GoogleTest)
gtest_discover_tests(${BINARY})
