@echo off
setlocal

for %%B in (debug release) do (
    echo.
    echo ========= Target: Windows-x64, BuildType: %%B =========
    echo.

    cmake --preset windows-x64-%%B
    if errorlevel 1 exit /b %errorlevel%

    cmake --build --preset windows-x64-%%B
    if errorlevel 1 exit /b %errorlevel%

    ctest --preset windows-x64-%%B
    if errorlevel 1 exit /b %errorlevel%
)

endlocal
