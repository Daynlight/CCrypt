cmake_minimum_required(VERSION 3.15)

project(AlgorithmsUnitTests LANGUAGES CXX)

set(src
  main.cpp
)

set(headers
  ../../
)

add_executable(AlgorithmsUnitTests ${src})
target_include_directories(AlgorithmsUnitTests PUBLIC ${headers})
target_link_libraries(AlgorithmsUnitTests PUBLIC ASD)


find_package(OpenSSL REQUIRED)
target_link_libraries(AlgorithmsUnitTests PRIVATE OpenSSL::Crypto)
