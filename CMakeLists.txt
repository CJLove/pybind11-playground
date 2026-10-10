cmake_minimum_required(VERSION 3.15)
project(my_pybind_project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Query the Python interpreter for the user site-packages path
execute_process(
    COMMAND python3 -m site --user-site
    OUTPUT_VARIABLE PYTHON_USER_SITE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Optional: Print out the directory to your CMake log for verification
message(STATUS "Python user site-packages: ${PYTHON_USER_SITE}")

# Find Python and pybind11 packages
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Define the python extension module
pybind11_add_module(example_module main.cpp)

target_link_libraries(example_module PRIVATE spdlog::spdlog)

# Alternatively, using the standard target approach:
# Python_add_library(example_module main.cpp)
# target_link_libraries(example_module PRIVATE pybind11::headers)

# To install to site: "${Python_SITEARCH}"

install(TARGETS example_module
    LIBRARY DESTINATION "${PYTHON_USER_SITE}"
)