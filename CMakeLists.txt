cmake_minimum_required(VERSION 3.27)
project(tundra)

set(CMAKE_CXX_STANDARD 17)

add_executable(tundra main.cpp
        Obj.cpp
        Obj.h
        Reducent.cpp
        Reducent.h
        Con1.cpp
        Con1.h
        Con2.cpp
        Con2.h)
