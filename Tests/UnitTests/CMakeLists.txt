cmake_minimum_required(VERSION 3.15)

project(UnitTests LANGUAGES CXX)

set(src
  Main.cpp
)

set(headers 
  Hash/
)

add_executable(UnitTests ${src})
target_include_directories(UnitTests PUBLIC ${headers})
target_link_libraries(UnitTests PUBLIC CCrypt)


find_package(OpenSSL REQUIRED)
target_link_libraries(UnitTests PRIVATE OpenSSL::Crypto)
