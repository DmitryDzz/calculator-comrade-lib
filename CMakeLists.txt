cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(CalculatorComrade
        VERSION 0.1
        LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include(CTest)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(calculator)

if(BUILD_TESTING)
    message(STATUS "Configuring with tests")
    add_subdirectory(tests)
else()
    message(STATUS "Configuring without tests")
endif()
