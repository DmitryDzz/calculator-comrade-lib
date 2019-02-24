@echo off

rem Android
rem -------

set PLATFORM=android-arm64-v8a
echo[ & echo Platform %PLATFORM% & echo -------------------------- & echo[
call build-platform.cmd %PLATFORM%

set PLATFORM=android-armeabi-v7a
echo[ & echo Platform %PLATFORM% & echo ---------------------------- & echo[
call build-platform.cmd %PLATFORM%

set PLATFORM=android-x86
echo[ & echo Platform %PLATFORM% & echo -------------------- & echo[
call build-platform.cmd %PLATFORM%

rem Windows
rem -------

set PLATFORM=windows-x86_64
echo[ & echo Platform %PLATFORM% & echo ----------------------- & echo[
call build-platform.cmd %PLATFORM%

set PLATFORM=windows-x86
echo[ & echo Platform %PLATFORM% & echo -------------------- & echo[
call build-platform.cmd %PLATFORM%

echo[ & echo Hope it works. Press something... & pause > nul