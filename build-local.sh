#!/usr/bin/env bash
cmake --preset "linux-x64-debug"
cmake --build --preset "linux-x64-debug"
ctest --preset "linux-x64-debug"
