@echo off

set PLATFORM=arm64-v8a
echo[ & echo Platform %PLATFORM% & echo ------------------ & echo[
call build-platform.cmd %PLATFORM%

set PLATFORM=armeabi-v7a
echo[ & echo Platform %PLATFORM% & echo -------------------- & echo[
call build-platform.cmd %PLATFORM%

set PLATFORM=win64
echo[ & echo Platform %PLATFORM% & echo -------------- & echo[
call build-platform.cmd %PLATFORM%

set PLATFORM=win32
echo[ & echo Platform %PLATFORM% & echo -------------- & echo[
call build-platform.cmd %PLATFORM%

echo[ & echo Hope it works. Press something... & pause > nul