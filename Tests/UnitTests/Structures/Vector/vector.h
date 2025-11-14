#pragma once 

#include "Assert.h"
#include "Structures/Vector/vector.h"


namespace Structures::UnitTests{
class Vector{
private:
  Tests::Assert assert;
public:
  bool runAll();
  void simpleTest();
};











inline bool Vector::runAll(){
  simpleTest();
  return assert.results("Vector");
};






void Vector::simpleTest() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  int a[20];
  int b[20] = {0};

  for(int i = 0; i < 20; i++)
    vector_emplace_back(&vec, (char*)&a[i]);
  
  for(int i = 0; i < 20; i++)
    vector_get(&vec, (char*)&b[i], i);
  
  for(int i = 0; i < 20; i++)
    assert.equal("Vector::simpleTest failed", std::to_string(b[i]), std::to_string(a[i]));

  vector_destroy(&vec);
};
};