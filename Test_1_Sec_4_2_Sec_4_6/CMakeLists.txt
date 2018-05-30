cmake_minimum_required(VERSION 2.8.12)
project(example)

add_subdirectory(../../GitHub/pybind11 ./build)
pybind11_add_module(example example.cpp)