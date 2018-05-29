cmake_minimum_required(VERSION 2.8.12)
project(example_YouTube)

add_subdirectory(../../GitHub/pybind11 ./build)
pybind11_add_module(example_YouTube example_YouTube.cpp)