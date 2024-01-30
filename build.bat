@echo off

REM Navigate to the build directory, create it if it doesn't exist
IF NOT EXIST build mkdir build
cd build

REM Configure the project with CMake
cmake ..

REM Build the project
cmake --build .

REM Navigate back to the root directory
cd ..

REM Run the executable
.\build\PixelTest.exe

pause
