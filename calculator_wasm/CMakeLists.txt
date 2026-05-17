if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "calculator_wasm can only be built with Emscripten")
endif()

add_executable(calculator_wasm
        src/main.cpp
)

target_link_libraries(calculator_wasm
        PRIVATE
        calculator_lib
)

target_compile_features(calculator_wasm
        PRIVATE
        cxx_std_11
)

set_target_properties(calculator_wasm PROPERTIES
        OUTPUT_NAME "calculator"
        SUFFIX ".js"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/wasm"
)

target_link_options(calculator_wasm
        PRIVATE
        "SHELL:--no-entry"

        "SHELL:-s WASM=1"
        "SHELL:-s MODULARIZE=1"
#        "SHELL:-s EXPORT_ES6=1"
        "SHELL:-s EXPORT_NAME=createCalculatorModule"
        "SHELL:-s ENVIRONMENT=web"
        "SHELL:-s ALLOW_MEMORY_GROWTH=1"

        "SHELL:-sEXPORTED_FUNCTIONS=['_GetCalculatorVersion','_CreateCalculator','_DisposeCalculator','_DisposeAll','_SetDisplayEventCallback','_CalculatorInput','_GetSize','_GetNegative','_GetError','_GetMemory','_GetPointPos','_GetDigit','_GetDisplayDigit','_ExportDump','_ImportDump','_malloc','_free']"

        "SHELL:-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap','getValue','setValue','UTF8ToString','HEAPU8','HEAP8']"
)