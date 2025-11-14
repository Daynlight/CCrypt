#pragma once 

#include "Assert.h"
#include "Structures/Vector/vector.h"


namespace Structures::UnitTests{
class Vector{
private:
  Tests::Assert assert;
public:
  bool runAll();
  
  void vectorInit();
  void vectorDestroy();

  void vectorResize();
  void vectorReserve();

  void vectorGet();
  void vectorSet();
  
  void vectorEmplaceBack();
};











inline bool Vector::runAll(){
  printf("==== Vector Tests ====\n");

  vectorInit();
  vectorDestroy();
  vectorResize();
  vectorReserve();
  vectorGet();
  vectorSet();
  vectorEmplaceBack();

  return assert.results("Vector");
};






inline void Vector::vectorInit() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  assert.equal("Vector::vectorInit cap", vec.cap, 1);
  assert.equal("Vector::vectorInit size", vec.size, 0);
  assert.equal("Vector::vectorInit size_of_el", vec.size_of_el, sizeof(int));
  assert.isNotNullptr("Vector::vectorInit data", vec.data);

  vector_destroy(&vec);
};






inline void Vector::vectorDestroy() {
  struct vector vec;
  vector_init(&vec, sizeof(int));
  vector_destroy(&vec);

  assert.isNullptr("Vector::vectorDestroy data", vec.data);
};






inline void Vector::vectorResize() {
  struct vector vec;
  vector_init(&vec, sizeof(int));
  unsigned int prev_cap = vec.cap;
  unsigned int estimated_cap = prev_cap * 2 + 1;

  vector_resize(&vec);
  unsigned int new_cap = vec.cap;

  assert.equal("Vector::vectorResize cap", new_cap, estimated_cap);
  assert.notEqual("Vector::vectorResize cap", new_cap, prev_cap);

  vector_destroy(&vec);
};






inline void Vector::vectorReserve() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  unsigned int additional_cap = 5;
  unsigned int prev_cap = vec.cap;
  unsigned int estimated_cap = prev_cap + additional_cap;

  vector_reserve(&vec, additional_cap);
  unsigned int new_cap = vec.cap;

  assert.equal("Vector::vectorReserve cap", new_cap, estimated_cap);
  assert.notEqual("Vector::vectorReserve cap", new_cap, prev_cap);

  vector_destroy(&vec);
};







inline void Vector::vectorGet() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  for(int i = 0; i < 20; i++)
    vector_emplace_back(&vec, (char*)&i);

  
  for(int i = 0; i < 20; i++){
    int a = 0;
    vector_get(&vec, (char*)&a, i);
    assert.equal("Vector::vectorGet", a, i);
  };

  vector_destroy(&vec);
};







inline void Vector::vectorSet() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  for(int i = 0; i < 20; i++)
    vector_emplace_back(&vec, (char*)&i);

  for(int i = 0; i < 20; i++){
    int a = 20 - i;
    vector_set(&vec, (char*)&a, i);
  };
  
  for(int i = 0; i < 20; i++){
    int a = 0;
    vector_get(&vec, (char*)&a, i);
    assert.equal("Vector::vectorSet", a, 20 - i);
  };

  vector_destroy(&vec);
};







inline void Vector::vectorEmplaceBack() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  int a[20];
  int b[20] = {0};

  for(int i = 0; i < 20; i++)
    vector_emplace_back(&vec, (char*)&a[i]);
  
  for(int i = 0; i < 20; i++)
    vector_get(&vec, (char*)&b[i], i);
  
  for(int i = 0; i < 20; i++)
    assert.equal("Vector::vectorEmplaceBack", b[i], a[i]);

  vector_destroy(&vec);
};
};