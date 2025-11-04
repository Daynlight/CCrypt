cmake_minimum_required(VERSION 3.15)

project(Hash LANGUAGES C)

set(src
    "src/sha256/sha256.c"
)

set(headers
    "include/"
)

add_library(Hash ${src})
target_include_directories(Hash PUBLIC ${headers})