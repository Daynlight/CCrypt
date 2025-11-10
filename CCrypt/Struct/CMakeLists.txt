cmake_minimum_required(VERSION 3.15)


project(Structures LANGUAGES C)


set(src
  struct.c
)

set(headers
  ${CMAKE_CURRENT_SOURCE_DIR}/
)


add_library(Structures ${src})
target_include_directories(Structures PUBLIC ${headers})
target_link_libraries(Structures PUBLIC Hash)