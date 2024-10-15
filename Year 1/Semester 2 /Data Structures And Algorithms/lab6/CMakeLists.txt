cmake_minimum_required(VERSION 3.28)
project(lab6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab6
        App.cpp
        IteratorMD.cpp
        IteratorMD.h
        MD.cpp
        MD.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
