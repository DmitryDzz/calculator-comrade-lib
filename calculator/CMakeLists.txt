set(
    SOURCES
        src/calculator.cpp
        include/calculator/calculator.h
        include/calculator/state.h
        include/calculator/operation.h
        include/calculator/display_register.h
        include/calculator/button.h
        include/calculator/register.h
        include/calculator/config.h)

set(TARGET calculator)

add_library(${TARGET} SHARED ${SOURCES})

target_include_directories(${TARGET} PUBLIC include)
