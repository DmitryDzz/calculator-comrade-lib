set(
    SOURCES
        src/libcalc.cpp
        src/calculator.cpp
        include/calculator/calculator.h
        include/calculator/state.h
        include/calculator/operation.h
        include/calculator/button.h
        include/calculator/register.h
        include/calculator/config.h
        src/math.cpp
)

set(TARGET calculator)

add_library(${TARGET} SHARED ${SOURCES})

target_include_directories(${TARGET} PUBLIC include)

# Android NDK include directory
if("${CMAKE_ANDROID_ARCH_ABI}" EQUAL "arm64-v8a")
    set(ANDROID_NDK_INCLUDE $ENV{ANDROID_NDK}/sysroot/usr/include)
    target_include_directories(${TARGET} PRIVATE ${ANDROID_NDK_INCLUDE})
    target_include_directories(${TARGET} PRIVATE ${ANDROID_NDK_INCLUDE}/aarch64-linux-android)
endif()
if("${CMAKE_ANDROID_ARCH_ABI}" EQUAL "armeabi-v7a")
    set(ANDROID_NDK_INCLUDE $ENV{ANDROID_NDK}/sysroot/usr/include)
    target_include_directories(${TARGET} PRIVATE ${ANDROID_NDK_INCLUDE})
    target_include_directories(${TARGET} PRIVATE ${ANDROID_NDK_INCLUDE}/arm-linux-androideabi)
endif()
