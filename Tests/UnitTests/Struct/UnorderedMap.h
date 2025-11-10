#pragma once 

#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

#include "unordered_map.h"

namespace UnitTests{
void StructUnorderedMapExample(){
  unordered_map map;
  unordered_map_init(&map, sizeof(int));

  int a = 2;
  unordered_map_set(&map, (char*)&a, "a");
  int b = 0;
  unordered_map_get(&map, (char*)&b, "a");

  printf("%d = %d\n", a, b);

  unordered_map_destroy(&map);
};

};