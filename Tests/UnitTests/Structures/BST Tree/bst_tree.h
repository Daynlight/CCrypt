#pragma once 

#include "Assert.h"
#include "Structures/Unordered_map/unordered_map.h"


namespace Structures::UnitTests{
class Bst_tree{
private:
  Tests::Assert assert;
public:
  bool runAll();

};











inline bool Bst_tree::runAll(){
  printf("==== BST Tree Tests ====\n");

  return assert.results("BST Tree");
};
};