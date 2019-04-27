set PLATFORM=%1
set OS=%2
set ARCHITECTURE=%3
set VERSION=%4

set BUILD_DIR=cmake-build-%PLATFORM%
rmdir %BUILD_DIR% /s /q
mkdir %BUILD_DIR%
cd %BUILD_DIR%
cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain-%PLATFORM%.cmake ..
mingw32-make

set OUTPUT_DIR=..\output
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%
if not exist %OUTPUT_DIR%\%OS% mkdir %OUTPUT_DIR%\%OS%
if not exist %OUTPUT_DIR%\%OS%\%ARCHITECTURE% mkdir %OUTPUT_DIR%\%OS%\%ARCHITECTURE%
del /Q %OUTPUT_DIR%\%OS%\%ARCHITECTURE%\*.* 2>nul
set SRC_DIR=lib\
if exist bin\ set SRC_DIR=bin\
set FILENAME=libcalculator_v%VERSION%
copy %SRC_DIR%\*.dll %OUTPUT_DIR%\%OS%\%ARCHITECTURE%\%FILENAME%.dll > nul 2> nul
copy %SRC_DIR%\*.so %OUTPUT_DIR%\%OS%\%ARCHITECTURE%\%FILENAME%.so > nul 2> nul
echo[ && echo "%FILENAME%" is copied to output\%OS%\%ARCHITECTURE%\

cd ..
