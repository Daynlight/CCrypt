cmake_minimum_required(VERSION 3.15)

project(AlgorithmsExample LANGUAGES CXX)


set(src
  main.cpp
)

add_executable(AlgorithmsExample ${src})
target_link_libraries(AlgorithmsExample PUBLIC ASD)