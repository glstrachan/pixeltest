#!/bin/bash

# Navigate to the build directory, create it if it doesn't exist
mkdir -p build
cd build

# Configure the project with CMake
cmake ..

# Build the project
cmake --build .

# Navigate back to the root directory
cd ..

# Run the executable
./build/PixelTest
