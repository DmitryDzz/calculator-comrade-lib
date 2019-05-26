# Calculator Comrade Library

![Calculator Comrade Library](https://dmitrydzz.github.io/calculator-comrade-pages/images/display_512x250.png)

This c++ library emulates a pocket calculator's microprocessor. It implements basic arithmetic operations (+, –, ×, ÷, %, √, MU, ±) and basic memory operations (M+, M-, MR, MC).

The emulator doesn't implement BCD encoding (binary-coded decimals) since it was designed for 8-bit microprocessors and higher. However, in all other aspects, the architecture and algorithms were scrupulously reproduced.

The library was used in [Calculator Comrade](https://dmitrydzz.github.io/calculator-comrade-pages/) Android app. The app is free and you can get it on Google Play.

[![Get it on Google Play](https://developer.android.com/images/brand/en_generic_rgb_wo_60.png)](https://play.google.com/store/apps/details?id=ru.robotmitya.comrade)

# License
Code released under the [MIT License](https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE).

# Getting Started
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

To build the libraries, run the script `build.cmd xxx`, where `xxx` is a version number. See the result in `output` directory.

## API

See the list of exported functions in [libcalc.h](https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/calculator/include/calculator/libcalc.h) file.

For embedded applications use Calculator class ([calculator.h](https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/calculator/include/calculator/calculator.h)).
