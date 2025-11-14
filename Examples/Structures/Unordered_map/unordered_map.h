#pragma once 

#include "Structures/Unordered_map/unordered_map.h"

#include <string.h>


namespace Structures::Examples{
void UnorderedMap(){
  printf("== StructuresUnorderedMapExample ==\n");
  
  // init
  struct unordered_map map;
  unordered_map_init(&map, sizeof(int));

  // set
  int a = 2;
  unordered_map_set(&map, (char*)&a, "a");

  // get
  int b = 0;
  unordered_map_get(&map, (char*)&b, "a");

  printf("%d = %d\n", a, b);

  // destroy
  unordered_map_destroy(&map);
};

};