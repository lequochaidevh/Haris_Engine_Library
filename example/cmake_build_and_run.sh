#!/bin/bash

rm -rf build
mkdir build
cd build

# Option: -DCMAKE_BUILD_TYPE=Debug
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./SandboxApp
