#include "SHA256.h"
#include "../../Assert.h"

int main(){
  UnitTests::Assert assert;
  UnitTests::SHA256 sha_tests;
  
  assert.assertion("SHA256 Tests", sha_tests.runAll());
  
  if(assert.results("Results"))
    return 0;
    
  return -1;
};