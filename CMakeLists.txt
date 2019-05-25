cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)

project(CalculatorComrade VERSION 0.1 LANGUAGES CXX)

if(($ENV{CLION_IDE}) AND (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows"))
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/toolchain-win64.cmake")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("calculator")

#if((${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore") OR ($ENV{CLION_IDE}))
##    message(**************************** " WindowsStore")
#    add_subdirectory("tests")
#endif()

if($ENV{SKIP_TESTS})
    message("********************************************************************************")
    message("*************************** Configuring without tests **************************")
    message("********************************************************************************")
else()
    message("********************************************************************************")
    message("**************************** Configuring with tests ****************************")
    message("********************************************************************************")
    add_subdirectory("tests")
endif()
