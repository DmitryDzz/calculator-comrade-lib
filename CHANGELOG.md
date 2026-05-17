# Changelog

## 1.0.0 (2026-05-17)

* Added modern CMake presets for supported build targets.
* Added cross-platform builds for Linux, Windows, Android, and WASM.
* Added WASM build support with Emscripten.
* Added Node.js-based WASM test execution.
* Improved GoogleTest-based unit tests.
* Added `calculator_lib` C API wrapper around the calculator core.
* Added shared/static library export support.
* Added export/import macros for building the public C API as a shared library.
* Added generated `libcalc_version.h` header with project version macros.
* Added clang-tidy configuration for source code checks.
* Improved source file header comments and SPDX license identifiers.
* Added project documentation updates.
* Documented that the public C API is not thread-safe.
* Preserved the lightweight C++11 calculator core for embedded-oriented use.

## 0.3.0 (2019-05-22)

* Improved the `importDump()` function.

## 0.2.0 (2019-05-19)

* Removed the `State` class.
* Added `exportDump()` and `importDump()` functions.

## 0.1.0 (2019-05-12)

* Fixed `ClearEntry` behavior after the square root operation.

## 0.1.0-alpha (2019-04-27)

* Fixed input behavior after the square root operation.
