
cmake_minimum_required (VERSION 3.8)

project ("ghost-ships-tests")

include_directories("../src")
file(GLOB SOURCES "../src/*.cpp")

add_executable (unit-tests  main.cpp catch.hpp test_address.cpp test_grid.cpp test_ships.cpp test_turns.cpp   ${SOURCES} )