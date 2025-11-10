cmake_minimum_required(VERSION 3.15)

project(CCrypt LANGUAGES C)

add_subdirectory(Hash)
add_subdirectory(Struct)

set(src
    ccrypt.c
)

add_library(CCrypt ${src})
target_link_libraries(CCrypt PUBLIC Hash)
target_link_libraries(CCrypt PUBLIC Structures)