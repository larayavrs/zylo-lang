@echo off
REM Ensure the build directory exists
if not exist build mkdir build

REM Compile the project
g++ -o ./build/zylo ./src/main.cxx ./src/terminal.cxx -I./src -I./src/utilities -std=c++17
