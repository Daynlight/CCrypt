cmake_minimum_required(VERSION 3.15)

project(HashUnitTests LANGUAGES CXX)

set(src
  Main.cpp
)

add_executable(HashUnitTests ${src})
target_include_directories(HashUnitTests PUBLIC ${headers})
target_link_libraries(HashUnitTests PUBLIC ASD)


find_package(OpenSSL REQUIRED)
target_link_libraries(HashUnitTests PRIVATE OpenSSL::Crypto)
