set(CALCULATOR_SOURCES
        src/calculator.cpp
        src/math.cpp

        include/calculator/types.h
        include/calculator/button_codes.h
        include/calculator/button.h
        include/calculator/calculator.h
        include/calculator/config.h
        include/calculator/math.h
        include/calculator/operation_codes.h
        include/calculator/operation.h
        include/calculator/option_codes.h
        include/calculator/register.h
)

add_library(calculator ${CALCULATOR_SOURCES})

target_include_directories(calculator
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(calculator
        PUBLIC
        cxx_std_11
)
