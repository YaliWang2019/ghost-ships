
cmake_minimum_required (VERSION 3.8)

project ("ghost-ships-demos")

include_directories("../src")
file(GLOB SOURCES "../src/*.cpp")

add_executable (game-part-demos  main.cpp demos.hpp demos.cpp ${SOURCES} )