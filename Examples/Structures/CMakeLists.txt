cmake_minimum_required(VERSION 3.15)

project(StructuresExample LANGUAGES CXX)

set(src
  main.cpp
)

add_executable(StructuresExample ${src})
target_link_libraries(StructuresExample PUBLIC ASD)