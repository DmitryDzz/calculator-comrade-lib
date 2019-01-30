set(SOURCES
        src/main.cpp
        src/basic_input_tests.cpp
        src/json.hpp
        src/register_tests.cpp
        src/state_tests.cpp
        #src/state_tests_json.cpp  #TODO DZZ Rename it to "complex_json_tests.cpp"
        src/calc_add_sub_tests.cpp
        src/calc_mul_tests.cpp
        src/calc_div_tests.cpp
        src/math_tests.cpp
        src/calc_helper.cpp
        src/special_tests.cpp
        src/libcalc_tests.cpp
)

set(TARGET tests)

add_subdirectory("googletest")

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} calculator gtest gmock)
