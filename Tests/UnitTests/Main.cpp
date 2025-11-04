#include "Hash/SHA256.h"
#include "Assert.h"

int main(){
  UnitTests::Assert assert;
  
  UnitTests::SHA256 sha_tests(&assert);
  sha_tests.runAll();
  assert.results("SHA256");

  return 0;
};