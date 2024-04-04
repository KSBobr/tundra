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
target_link_libraries(tundra PRIVATE m)
set(SFML_ROOT ${CMAKE_SOURCE_DIR}/sfml)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)
FILE(
        COPY "${CMAKE_CURRENT_SOURCE_DIR}/textures"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)
if (SFML_FOUND)
    # Добавление headers
    target_include_directories(tundra PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(tundra PRIVATE sfml-graphics sfml-window sfml-system)
endif ()
