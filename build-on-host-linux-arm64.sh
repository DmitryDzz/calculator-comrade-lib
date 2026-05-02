#!/usr/bin/env bash
set -euo pipefail

for BUILD_TYPE in debug release; do
    echo -e "\n========= Target: Linux-arm64, BuildType: ${BUILD_TYPE} =========\n"
    cmake --preset "linux-arm64-${BUILD_TYPE}"
    cmake --build --preset "linux-arm64-${BUILD_TYPE}"
    ctest --preset "linux-arm64-${BUILD_TYPE}"
done
