cmake_minimum_required(VERSION 3.27)
project(lab2_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2_4 main.c
        service.h
        service.c
        teste.c
        lista.h
        lista.c
        entitate.h
        entitate.c
        validator.h
        validator.c)
