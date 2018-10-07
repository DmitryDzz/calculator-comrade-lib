set(
    SOURCES 
        "src/main.cpp"
        "src/main_test.cpp"
)

set(TARGET tests)

add_subdirectory("googletest")

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} calculator gtest gmock)
