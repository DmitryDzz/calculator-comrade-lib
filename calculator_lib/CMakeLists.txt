set(CALCULATOR_LIB_SOURCES
        src/libcalc.cpp
        include/calculator/libcalc.h
)

add_library(calculator_lib ${CALCULATOR_LIB_SOURCES})

target_include_directories(calculator_lib
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(calculator_lib
        PUBLIC
        calculator
)

target_compile_features(calculator_lib
        PUBLIC
        cxx_std_11
)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(calculator_lib PRIVATE CALCULATOR_LIB_BUILD)
else()
    target_compile_definitions(calculator_lib PUBLIC CALCULATOR_LIB_STATIC)
endif()
