cmake_minimum_required(VERSION 3.15)

project(HashExample LANGUAGES CXX)

set(src
  main.cpp
)

add_executable(HashExample ${src})
target_link_libraries(HashExample PUBLIC ASD)