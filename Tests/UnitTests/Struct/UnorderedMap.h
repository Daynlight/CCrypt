#pragma once 

#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

#include "unordered_map.h"

namespace UnitTests{
class Unordered_map{
private:
  Assert assert;
public:
  bool runAll();
  void simpleTest();
};
};




inline bool UnitTests::Unordered_map::runAll(){
  simpleTest();
  return assert.results("Unordered_map");
};




void UnitTests::Unordered_map::simpleTest() {
  unordered_map map;
  unordered_map_init(&map, sizeof(int));

  int a[20];
  int b[20] = {0};

  for(int i = 0; i < 20; i++)
    unordered_map_set(&map, (char*)&a[i], std::to_string(i).c_str());
  
  for(int i = 0; i < 20; i++)
    unordered_map_get(&map, (char*)&b[i], std::to_string(i).c_str());
  
  for(int i = 0; i < 20; i++)
    assert.equal("Unordered_map::simpleTest failed", std::to_string(b[i]), std::to_string(a[i]));

  unordered_map_destroy(&map);
};