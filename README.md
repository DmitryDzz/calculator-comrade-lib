# calculator-comrade-lib
Simulator of a simple calculator with basic arithmetic operations (+, ⁻, ×, ÷, %, √) and M/RM functions.

# Quick start
## Clone the project:
`git clone --recurse-submodules git@github.com:DmitryDzz/calculator-comrade-lib.git`

## How to build in pure cmake
Create a directory next to the project:<br>
`mkdir build-cmake`<br>
`cd build-cmake`

Generate a build system.<br>
Linux: `cmake -G "Unix Makefiles" ../calculator-comrade-lib`<br>
Windows: `cmake -G "MinGW Makefiles" ..\calculator-comrade-lib`<br>

Build the project.<br>
Linux: `make`<br>
Windows: `mingw32-make`
