cmake_minimum_required(VERSION 3.0.0)
project(petri VERSION 0.1.0)

add_library(conway conway.cpp)



add_executable(petri evolve.cpp)

find_package(OpenMP REQUIRED)
target_link_libraries(petri PUBLIC OpenMP::OpenMP_CXX)

target_link_libraries(petri PUBLIC conway)


