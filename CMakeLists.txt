cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(CalculatorComrade
        VERSION 0.1
        LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(CALCULATOR_BUILD_LIB "Build calculator C API wrapper library" ON)
option(CALCULATOR_BUILD_WASM "Build calculator WebAssembly module" OFF)

include(CTest)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(calculator)

if(CALCULATOR_BUILD_LIB)
    add_subdirectory(calculator_lib)
endif()

if(CALCULATOR_BUILD_WASM)
    add_subdirectory(calculator_wasm)
endif()

if(BUILD_TESTING)
    message(STATUS "Configuring with tests")
    add_subdirectory(tests)
else()
    message(STATUS "Configuring without tests")
endif()
