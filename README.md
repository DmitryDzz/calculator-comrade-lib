# Calculator Comrade Library

![Calculator Comrade Library](https://dmitrydzz.github.io/calculator-comrade-pages/images/display_512x250.png)

This C++ library emulates a pocket calculator's microprocessor. It implements basic arithmetic operations (+, –, ×, ÷, %, √, MU, ±) and basic memory operations (M+, M-, MR, MC).

The emulator doesn't implement BCD encoding (binary-coded decimals) since it was designed for 8-bit microprocessors and higher. However, in all other aspects, the architecture and algorithms were scrupulously reproduced.

The library was used in [Calculator Comrade](https://dmitrydzz.github.io/calculator-comrade-pages/) Android app. The app is free, and you can get it on Google Play.

[![Get it on Google Play](https://developer.android.com/images/brand/en_generic_rgb_wo_60.png)](https://play.google.com/store/apps/details?id=ru.robotmitya.comrade)

## License
The code was released under the [MIT License](https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE).

## Project structure

The project is split into two parts:

- `calculator` – the calculator core.
- `calculator_lib` – the C-style library wrapper.

### calculator

`calculator` contains the actual calculator engine.

This part is intended to stay small, portable, and suitable for embedded projects. The code is written in a conservative C++ style and avoids platform-specific APIs.

For embedded applications, this is the preferred part of the project to reuse. The `calculator` directory is intentionally kept self-contained so it can be copied into a small embedded project if needed.

Use the `Calculator` class directly when integrating the core into firmware or other low-level environments.

The CMake target currently requires C++11. The core is intentionally kept simple so that it can later be adapted to older or more restricted embedded toolchains if needed.

### calculator_lib

`calculator_lib` provides the exported C-style API declared in `libcalc.h`.

This layer is intended for integration scenarios where a plain C-compatible interface is more convenient, for example desktop applications, mobile applications, WebAssembly bindings, or foreign-function interfaces.

Unlike the core, this layer may use heavier C++ facilities internally, such as STL containers and dynamic allocation. It is not the recommended layer for very small microcontrollers.

The C API is not thread-safe. Calls that create, dispose, or use calculator instances must be externally synchronized if they can be made from multiple threads.

## Getting started

The project uses CMake Presets for configuring and building the library.

The recommended build generator is Ninja. The recommended compiler is Clang.

### Prerequisites

Common tools:

- CMake 3.21 or newer
- Ninja
- Clang / Clang++
- Git

On Ubuntu/Debian-based systems:

```bash
sudo apt update
sudo apt install cmake ninja-build clang git
```

The project uses GoogleTest as a Git submodule, so clone the repository with submodules:

```bash
git clone --recurse-submodules https://github.com/DmitryDzz/calculator-comrade-lib.git
cd calculator-comrade-lib
```

If the repository was cloned without submodules, initialize them manually:

```bash
git submodule update --init --recursive
```

### Linux x64

Configure, build, and run tests:

```bash
cmake --preset linux-x64-debug
cmake --build --preset linux-x64-debug
ctest --preset linux-x64-debug
```

Release build:

```bash
cmake --preset linux-x64-release
cmake --build --preset linux-x64-release
ctest --preset linux-x64-release
```

### Linux arm64

The Linux arm64 presets are intended to be used on a native Linux arm64 host, for example Raspberry Pi.

Debug build:

```bash
cmake --preset linux-arm64-debug
cmake --build --preset linux-arm64-debug
ctest --preset linux-arm64-debug
```

Release build:

```bash
cmake --preset linux-arm64-release
cmake --build --preset linux-arm64-release
ctest --preset linux-arm64-release
```

### Windows x64

The Windows x64 presets are intended to be used on a Windows x64 host.

Use a terminal where the Visual Studio / MSVC build environment is already initialized, for example Developer PowerShell for VS or Developer Command Prompt for VS.

The project is configured to use Ninja and Clang on Windows as well.

Debug build:

```powershell
cmake --preset windows-x64-debug
cmake --build --preset windows-x64-debug
ctest --preset windows-x64-debug
```

Release build:

```powershell
cmake --preset windows-x64-release
cmake --build --preset windows-x64-release
ctest --preset windows-x64-release
```

### Android

Android builds are intended to be performed from a Linux x64 host.

Install Android SDK and Android NDK first. See the official Android documentation:

- Android Studio / SDK installation: https://developer.android.com/studio
- Android NDK installation: https://developer.android.com/ndk/guides

The `ANDROID_NDK_HOME` environment variable must point to the installed Android NDK directory:

```bash
export ANDROID_NDK_HOME=/path/to/android-ndk
```

Build for Android arm64-v8a:

```bash
cmake --preset android-arm64-debug
cmake --build --preset android-arm64-debug
```

```bash
cmake --preset android-arm64-release
cmake --build --preset android-arm64-release
```

Build for Android armeabi-v7a:

```bash
cmake --preset android-armv7-debug
cmake --build --preset android-armv7-debug
```

```bash
cmake --preset android-armv7-release
cmake --build --preset android-armv7-release
```

The test executable is built for Android as part of the regular build. Running it requires deploying it to an Android device or emulator manually, for example with `adb`.

### WebAssembly

WebAssembly builds are intended to be performed from a Linux x64 host.

Install Emscripten SDK first:

- Emscripten SDK installation: https://emscripten.org/docs/getting_started/downloads.html

The `EMSDK` environment variable must point to the installed Emscripten SDK directory:

```bash
export EMSDK=/path/to/emsdk
```

Before building, make sure the Emscripten environment is activated according to the Emscripten SDK instructions.

Debug build:

```bash
cmake --preset wasm-debug
cmake --build --preset wasm-debug
```

Release build:

```bash
cmake --preset wasm-release
cmake --build --preset wasm-release
```

The test executable is built for WebAssembly as part of the regular build. Running WebAssembly tests may require an additional runtime setup, such as Node.js or another WASM-compatible test runner.

### Available presets

To list available configure presets:

```bash
cmake --list-presets
```

To list available build presets:

```bash
cmake --build --list-presets
```

To list available test presets:

```bash
ctest --list-presets
```

### Build output

Build artifacts are generated under the `build` directory, using the preset name as the build directory name.

For example:

```text
build/linux-x64-debug
build/linux-x64-release
build/android-arm64-debug
build/wasm-debug
```

## Build options

- `BUILD_TESTING=ON/OFF` – builds unit tests.
- `CALCULATOR_BUILD_LIB=ON/OFF` – builds the C-style wrapper library.
- `BUILD_SHARED_LIBS=ON/OFF` – builds shared/static libraries where applicable.

## Host build scripts

The repository includes convenience scripts for building all presets that are expected to work on a particular host platform.

These scripts are intended for local validation before pushing changes or preparing a release. They run the corresponding CMake configure and build presets for both `debug` and `release` configurations. Where tests are supported on the host platform, the scripts also run the matching CTest presets.

Available scripts:

- `build-on-host-linux-x64.sh` – builds and tests Linux x64, then builds Android arm64, Android armv7, and WebAssembly presets. Android and WebAssembly test binaries are built, but not executed by this script.
- `build-on-host-linux-arm64.sh` – builds and tests Linux arm64 presets. This script is intended for native Linux arm64 hosts, for example Raspberry Pi.
- `build-on-host-windows-x64.cmd` – builds and tests Windows x64 presets. This script should be run from a terminal where the Visual Studio / MSVC build environment is already initialized, such as Developer PowerShell for VS or Developer Command Prompt for VS.

The scripts are thin wrappers around CMake Presets. They do not replace the individual preset commands described above; they only provide a quicker way to run all relevant builds for the current host.
