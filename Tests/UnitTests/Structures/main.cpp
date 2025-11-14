#include "Assert.h"
#include "Unordered_map/unordered_map.h"
#include "Vector/vector.h"
#include "BST Tree/bst_tree.h"

int main(){
  Tests::Assert assert;
  Structures::UnitTests::Vector vector_tests;
  Structures::UnitTests::Unordered_map unordered_map_tests;
  Structures::UnitTests::Bst_tree bst_tree_tests;

  assert.assertion("Vector Tests", vector_tests.runAll());
  assert.assertion("Unordered_map Tests", unordered_map_tests.runAll());
  assert.assertion("Bst Tree Tests", bst_tree_tests.runAll());


  if(assert.results("Results"))
    return 0;
    
  return -1;
};