cmake_minimum_required(VERSION 3.15)

add_subdirectory(CCrypt)

add_subdirectory(Tests)
add_subdirectory(Examples)

enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)