cmake_minimum_required(VERSION 3.28)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories("TAD Multime/Proiect C++/Multime (cu rel)")
include_directories("TAD Multime/Teste(cu relatie)")

add_executable(lab4
        App.cpp
        IteratorMultime.cpp
        IteratorMultime.h
        Multime.cpp
        Multime.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
