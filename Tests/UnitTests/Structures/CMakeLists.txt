cmake_minimum_required(VERSION 3.15)

project(StructuresUnitTests LANGUAGES CXX)

set(src
  main.cpp
)

set(headers
  ../../
)

add_executable(StructuresUnitTests ${src})
target_include_directories(StructuresUnitTests PUBLIC ${headers})
target_link_libraries(StructuresUnitTests PUBLIC ASD)