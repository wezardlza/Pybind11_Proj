cmake_minimum_required(VERSION 2.8.12)
project(chapter8)

add_subdirectory(../../GitHub/pybind11 ./build)
pybind11_add_module(chapter8 chapter8.cpp)