set(
    SOURCES 
        "src/main.cpp"
        "include/calculator/main.h"
)

set(TARGET calculator)

add_library(${TARGET} SHARED ${SOURCES})

target_include_directories(${TARGET} PUBLIC "include")
