#include "Assert.h"
#include "SHA256/sha256.h"

int main(){
  Tests::Assert assert;
  Algorithms::UnitTests::SHA256 sha_tests;
  
  assert.assertion("SHA256 Tests", sha_tests.runAll());
  
  if(assert.results("Results"))
    return 0;
    
  return -1;
};