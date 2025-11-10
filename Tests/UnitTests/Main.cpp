#include "Hash/SHA256.h"
#include "Struct/UnorderedMap.h"
#include "Assert.h"

int main(){
  UnitTests::Assert assert;
  UnitTests::SHA256 sha_tests;
  UnitTests::Unordered_map unordered_map_tests;

  assert.assertion("SHA256 Tests", sha_tests.runAll());
  assert.assertion("Unordered_map Tests", unordered_map_tests.runAll());

  if(assert.results("Results"))
    return 0;
    
  return -1;
};