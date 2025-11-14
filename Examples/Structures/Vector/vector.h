#pragma once 

#include "Structures/Vector/vector.h"

#include <stdio.h>

void StructuresVectorExample(){
  printf("== StructuresVectorExample ==\n");
  
  // init
  struct vector vec;
  vector_init(&vec, sizeof(int));
  vector_reserve(&vec, 10);
  
  // emplace
  for(int i = 0; i < 10; i++)
    vector_emplace_back(&vec, (char*)&i);

  // set
  int data = 5;
  vector_set(&vec, (char*)&data, 3);

  // get
  printf("[");
  for(int i = 0; i < 10; i++){
    int get = 0;
    vector_get(&vec, (char*)&get, i);
    if(i == 0)
      printf("%d", get);
    else
      printf(", %d", get);
  }
  printf("]\n");

  // destroy
  vector_destroy(&vec);
};