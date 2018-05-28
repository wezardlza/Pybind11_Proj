cmake_minimum_required(VERSION 2.8.12)
project(example_class_pet)

add_subdirectory(../../GitHub/pybind11 ./build)
pybind11_add_module(example_class_pet example_class_pet.cpp)