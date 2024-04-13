cmake_minimum_required(VERSION 3.28)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1
        "Colectie.h"
        "IteratorColectie.h"
        "Colectie.cpp"
        "IteratorColectie.cpp"
        "App.cpp"
        "TestExtins.cpp"
        "TestExtins.h"
        "TestScurt.cpp"
        "TestScurt.h")
