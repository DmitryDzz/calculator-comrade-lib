cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)

project(CalculatorComrade VERSION 0.1 LANGUAGES CXX)

option(BUILD_STATIC_LIBS "Build the static library" ON)
option(BUILD_SHARED_LIBS "Build the shared library" ON)
option(BUILD_TESTS "Build tests" ON)

if(($ENV{CLION_IDE}) AND (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows"))
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/toolchain-win64.cmake")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("calculator")

if(${BUILD_TESTS})
    message("********************************************************************************")
    message("**************************** Configuring with tests ****************************")
    message("********************************************************************************")
    add_subdirectory("tests")
else()
    message("********************************************************************************")
    message("*************************** Configuring without tests **************************")
    message("********************************************************************************")
endif()
