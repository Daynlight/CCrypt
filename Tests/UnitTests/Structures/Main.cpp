#include "Unordered_map.h"
#include "../../Assert.h"

int main(){
  UnitTests::Assert assert;
  UnitTests::Unordered_map unordered_map_tests;

  assert.assertion("Unordered_map Tests", unordered_map_tests.runAll());

  if(assert.results("Results"))
    return 0;
    
  return -1;
};