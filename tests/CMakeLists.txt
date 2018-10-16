set(
    SOURCES 
        "src/main.cpp"
        "src/basic_input_tests.cpp"
)

set(TARGET tests)

add_subdirectory("googletest")

add_executable(${TARGET} ${SOURCES})

#set(JSON_BuildTests OFF CACHE INTERNAL "")
#add_subdirectory(nlohmann_json)

target_link_libraries(${TARGET} calculator gtest gmock)
#target_link_libraries(${TARGET} calculator gtest gmock nlohmann_json::nlohmann_json)
