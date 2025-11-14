cmake_minimum_required(VERSION 3.15)

add_subdirectory(ASD)

add_subdirectory(Tests)
add_subdirectory(Examples)

enable_testing()

add_test(NAME StructuresUnitTests COMMAND StructuresUnitTests)
add_test(NAME AlgorithmsUnitTests COMMAND AlgorithmsUnitTests)
