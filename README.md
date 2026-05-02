# Calculator Comrade Library

![Calculator Comrade Library](https://dmitrydzz.github.io/calculator-comrade-pages/images/display_512x250.png)

This C++ library emulates a pocket calculator's microprocessor. It implements basic arithmetic operations (+, –, ×, ÷, %, √, MU, ±) and basic memory operations (M+, M-, MR, MC).

The emulator doesn't implement BCD encoding (binary-coded decimals) since it was designed for 8-bit microprocessors and higher. However, in all other aspects, the architecture and algorithms were scrupulously reproduced.

The library was used in [Calculator Comrade](https://dmitrydzz.github.io/calculator-comrade-pages/) Android app. The app is free, and you can get it on Google Play.

[![Get it on Google Play](https://developer.android.com/images/brand/en_generic_rgb_wo_60.png)](https://play.google.com/store/apps/details?id=ru.robotmitya.comrade)

# License
The code was released under the [MIT License](https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE).

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

Use a terminal where the Visual Studio / MSVC build environment is already initialized, for example **Developer PowerShell for VS** or **Developer Command Prompt for VS**.

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

## API

See the list of exported functions in [libcalc.h](https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/calculator/include/calculator/libcalc.h) file.

For embedded applications, use Calculator class ([calculator.h](https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/calculator/include/calculator/calculator.h)).
