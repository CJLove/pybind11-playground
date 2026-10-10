#!/bin/bash

cmake -B build -S . -Dpybind11_DIR=$(python3 -c "import pybind11; print(pybind11.get_cmake_dir())") -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

cmake --build build