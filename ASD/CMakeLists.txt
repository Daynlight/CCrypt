cmake_minimum_required(VERSION 3.15)

project(ASD LANGUAGES C)

set(src
    asd.c
    src/Algorithms/Hash/SHA256/sha256.c
)

set(headers
    "include/"
)

add_library(ASD ${src})

target_include_directories(ASD PUBLIC ${headers})