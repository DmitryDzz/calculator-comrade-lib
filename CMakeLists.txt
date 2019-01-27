cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

if($ENV{CLION_IDE})
#    message(**************************** " CLION")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/toolchain-win64.cmake")
else()
#    message(**************************** " NOT CLION")
endif()

set(CMAKE_CXX_STANDARD 14)

project(CalculatorComrade VERSION 0.1 LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("calculator")

if((${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore") OR ($ENV{CLION_IDE}))
#    message(**************************** " WindowsStore")
    add_subdirectory("tests")
endif()
