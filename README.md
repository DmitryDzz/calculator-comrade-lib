# calculator-comrade-lib
This c++ library emulates a pocket calculator's microprocessor. It implements basic arithmetic operations (+, –, ×, ÷, %, √, MU, ±) and basic memory operations (M+, M-, MR, MC).

The emulator doesn't implement BCD encoding (binary-coded decimals) since it was designed for 8-bit microprocessors and higher. However, in all other aspects, the architecture and algorithms were scrupulously reproduced.

# Quick start
## Clone the project:
`git clone --recurse-submodules git@github.com:DmitryDzz/calculator-comrade-lib.git`

## How to build in pure cmake
Create a directory next to the project:<br>
`mkdir build-cmake`<br>
`cd build-cmake`

Generate a build system:<br>
Linux: `cmake -G "Unix Makefiles" ../calculator-comrade-lib`<br>
Windows: `cmake -G "MinGW Makefiles" ..\calculator-comrade-lib`<br>

Build the project:<br>
Linux: `make`<br>
Windows: `mingw32-make`

Run tests:<br>
Linux: `./bin/tests`<br>
Windows: `bin\tests.exe`

## How to build a cross-platform release
Currently, only Windows host system is supported.

The library is generated for the following target systems:
* Android arm64-v8a
* Android armeabi-v7a
* Android x86
* Windows x86
* Windows x86_64
