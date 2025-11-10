cmake_minimum_required(VERSION 3.15)

project(StructExample LANGUAGES CXX)

set(src
  main.cpp
)

add_executable(StructExample ${src})
target_link_libraries(StructExample PUBLIC CCrypt)