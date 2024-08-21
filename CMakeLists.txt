# Establish the minimum version of CMake required to build the project
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(zylolang)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target (inside the source directory)
add_executable(zylolang src/main.cc)

# Include the headers directory
target_include_directories(zylolang PUBLIC src)

# Add the executable target
add_executable(zylolang src/main.cc)
