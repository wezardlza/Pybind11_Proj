cmake_minimum_required(VERSION 2.8.12)
project(example_class)

add_subdirectory(../../GitHub/pybind11 ./build)
pybind11_add_module(example_class example_class.cpp)