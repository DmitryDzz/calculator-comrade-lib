set(SOURCES
        src/main.cpp
        src/basic_input_tests.cpp
        src/register_tests.cpp
        src/add_sub_input_tests.cpp
        src/mul_input_tests.cpp
        src/div_input_tests.cpp
        src/math_tests.cpp
        src/calc_helper.cpp
        src/special_tests.cpp
        src/libcalc_tests.cpp
        src/percent_input_tests.cpp
        src/mem_input_tests.cpp
        src/sqrt_input_tests.cpp
        src/mu_input_tests.cpp
        src/dump_tests.cpp
)

set(TARGET tests)

add_subdirectory("googletest")

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} calculator gtest gmock)
