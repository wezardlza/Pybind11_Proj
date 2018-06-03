cmake_minimum_required(VERSION 2.8.12)
project(chapter8_1)

add_subdirectory(../../GitHub/pybind11 ./build)
pybind11_add_module(chapter8_1 chapter8_1.cpp)