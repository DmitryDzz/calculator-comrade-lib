#!/usr/bin/env bash
set -euo pipefail

for BUILD_TYPE in debug release; do
    echo -e "\n========= Target: Linux-x64, BuildType: ${BUILD_TYPE} =========\n"
    cmake --preset "linux-x64-${BUILD_TYPE}"
    cmake --build --preset "linux-x64-${BUILD_TYPE}"
    ctest --preset "linux-x64-${BUILD_TYPE}"

    echo -e "\n========= Target: Android arm64, BuildType: ${BUILD_TYPE} =========\n"
    cmake --preset "android-arm64-${BUILD_TYPE}"
    cmake --build --preset "android-arm64-${BUILD_TYPE}"

    echo -e "\n========= Target: Android armv7, BuildType: ${BUILD_TYPE} =========\n"
    cmake --preset "android-armv7-${BUILD_TYPE}"
    cmake --build --preset "android-armv7-${BUILD_TYPE}"

    echo -e "\n========= Target: WebAssembly, BuildType: ${BUILD_TYPE} =========\n"
    cmake --preset "wasm-${BUILD_TYPE}"
    cmake --build --preset "wasm-${BUILD_TYPE}"
done