cmake_minimum_required(VERSION 3.28)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

include_directories("TAD Coada cu Prioritati/Proiect C++")
include_directories("TAD Coada cu Prioritati/Teste")

add_executable(lab3
        "TAD Coada cu Prioritati/Proiect C++/App.cpp"
        "TAD Coada cu Prioritati/Proiect C++/CP.cpp"
        "TAD Coada cu Prioritati/Proiect C++/CP.h"
        "TAD Coada cu Prioritati/Teste/TestExtins.cpp"
        "TAD Coada cu Prioritati/Teste/TestExtins.h"
        "TAD Coada cu Prioritati/Teste/TestScurt.cpp"
        "TAD Coada cu Prioritati/Teste/TestScurt.h")
