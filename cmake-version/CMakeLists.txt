
cmake_minimum_required (VERSION 3.8)

project ("cmake-version")

include_directories("../game-logic/src")
file(GLOB SOURCES "../game-logic/src/*.cpp")

add_executable (ghost-ships  main.cpp   ${SOURCES} )