@echo off

set VERSION=%1

set SKIP_TESTS=TRUE

rem Android
rem -------

set OS=android

set ARCHITECTURE=arm64-v8a
set PLATFORM=%OS%-%ARCHITECTURE%
echo[ & echo Platform %PLATFORM% & echo -------------------------- & echo[
call build-platform.cmd %PLATFORM% %OS% %ARCHITECTURE% %VERSION%

set ARCHITECTURE=armeabi-v7a
set PLATFORM=%OS%-%ARCHITECTURE%
echo[ & echo Platform %PLATFORM% & echo ---------------------------- & echo[
call build-platform.cmd %PLATFORM% %OS% %ARCHITECTURE% %VERSION%

set ARCHITECTURE=x86
set PLATFORM=%OS%-%ARCHITECTURE%
echo[ & echo Platform %PLATFORM% & echo -------------------- & echo[
call build-platform.cmd %PLATFORM% %OS% %ARCHITECTURE% %VERSION%

rem Windows
rem -------

set OS=windows

set ARCHITECTURE=x86_64
set PLATFORM=%OS%-%ARCHITECTURE%
echo[ & echo Platform %PLATFORM% & echo ----------------------- & echo[
call build-platform.cmd %PLATFORM% %OS% %ARCHITECTURE% %VERSION%

set ARCHITECTURE=x86
set PLATFORM=%OS%-%ARCHITECTURE%
echo[ & echo Platform %PLATFORM% & echo -------------------- & echo[
call build-platform.cmd %PLATFORM% %OS% %ARCHITECTURE% %VERSION%

echo[ & echo Hope it works. Press something... & pause > nul
