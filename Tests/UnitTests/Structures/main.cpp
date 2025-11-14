#include "Assert.h"
#include "Unordered_map/unordered_map.h"
#include "Vector/vector.h"

int main(){
  Tests::Assert assert;
  Structures::UnitTests::Unordered_map unordered_map_tests;
  Structures::UnitTests::Vector vector_tests;

  assert.assertion("Unordered_map Tests", unordered_map_tests.runAll());
  assert.assertion("Vector Tests", vector_tests.runAll());


  if(assert.results("Results"))
    return 0;
    
  return -1;
};