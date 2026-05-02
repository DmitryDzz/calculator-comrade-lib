set(CALCULATOR_TEST_SOURCES
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

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_executable(calculator_tests ${CALCULATOR_TEST_SOURCES})

set_target_properties(calculator_tests
        PROPERTIES
        OUTPUT_NAME tests
)

target_link_libraries(calculator_tests
        PRIVATE
        calculator
        GTest::gtest
        GTest::gmock
)

add_test(
        NAME calculator_tests
        COMMAND calculator_tests
)
