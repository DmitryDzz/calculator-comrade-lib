set(SOURCES
        src/main.cpp
        src/basic_input_tests.cpp
        src/json.hpp
        src/register_tests.cpp
        src/add_sub_tests.cpp
        src/state_tests.cpp
        #src/state_tests_json.cpp
)

set(TARGET tests)

add_subdirectory("googletest")

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} calculator gtest gmock)
