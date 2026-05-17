# Calculator Comrade Library
#
# Copyright (c) 2019-2026 Dmitry Dzakhov (dmitrydzz)
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(CalculatorComrade
        VERSION 1.0.0
        LANGUAGES C CXX
)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(CALCULATOR_BUILD_LIB "Build calculator C API wrapper library" ON)
option(CALCULATOR_BUILD_WASM "Build calculator WebAssembly module" OFF)

include(CTest)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/calculator_lib/include/calculator/libcalc_version.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/libcalc_version.h
        @ONLY
)

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
