set PLATFORM=%1
set BUILD_DIR=cmake-build-%PLATFORM%
rmdir %BUILD_DIR% /s /q
mkdir %BUILD_DIR%
cd %BUILD_DIR%
cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain-%PLATFORM%.cmake ..
mingw32-make


rem set UNITY_DIR=..\..\TestAndroidDreamPlayer\Assets\Plugins\Android\libs\%PLATFORM%

rem del %UNITY_DIR%\libLolaPlayer.so 2>nul
rem copy libLolaPlayer.so %UNITY_DIR%\ >nul && ^
rem echo[ && echo "libLolaPlayer.so" is copied

rem del %UNITY_DIR%\libLolaPlayer.a 2>nul
rem copy libLolaPlayer.a %UNITY_DIR%\ >nul && ^
rem echo[ && echo "libLolaPlayer.a" is copied


cd ..
