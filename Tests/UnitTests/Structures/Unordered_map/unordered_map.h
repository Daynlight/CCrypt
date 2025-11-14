#pragma once 

#include "Assert.h"
#include "Structures/Unordered_map/unordered_map.h"


namespace Structures::UnitTests{
class Unordered_map{
private:
  Tests::Assert assert;
public:
  bool runAll();
  
  void unorderedMapHashFun();

  void unorderedMapInit();
  void unorderedMapDestroy();

  void unorderedMapSetAndGet();
};











inline bool Unordered_map::runAll(){
  printf("==== Unordered_map Tests ====\n");

  unorderedMapHashFun();
  unorderedMapInit();
  unorderedMapDestroy();
  unorderedMapSetAndGet();
  
  return assert.results("Unordered_map");
};






std::string randomString(int length){
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::string result;
  result.reserve(length);
  
  for (int i = 0; i < length; ++i) {
    result += charset[rand() % (sizeof(charset) - 1)];
  };

  return result;
};






inline void Unordered_map::unorderedMapHashFun(){
  unsigned int tests = 20000;
  unsigned int string_size = 20;
  float eps = 0.02f;
  
  int sum[BUCKETS] = {0};
  unsigned int total = 0;
  
  for(int i = 0; i < tests; i++){
    std::string key = randomString(string_size);
    sum[unordered_map_hash_fun(key.c_str()) % BUCKETS]++;
    total++;
  };

  for(int i = 0; i < BUCKETS; i++){ // |delta x - x| < eps
    float average = float(sum[i]) / total;
    assert.lt("Unordered_map::unorderedMapHashFun", abs(average - (float(1) / BUCKETS)), eps);
  };
};






inline void Unordered_map::unorderedMapInit() {
  struct unordered_map map;
  unordered_map_init(&map, sizeof(int));

  assert.equal("Unordered_map::unorderedMapInit cap", map.data.cap, 1);
  assert.equal("Unordered_map::unorderedMapInit size", map.data.size, 0);
  assert.equal("Unordered_map::unorderedMapInit size_of_el", map.data.size_of_el, sizeof(int));
  assert.isNotNullptr("Unordered_map::unorderedMapInit data", map.data.data);
  for(int i = 0; i < BUCKETS; i++)
      assert.isNotNullptr("Unordered_map::unorderedMapInit bucket", map.buckets[i].data);

  unordered_map_destroy(&map);
};






inline void Unordered_map::unorderedMapDestroy() {
  struct unordered_map map;
  unordered_map_init(&map, sizeof(int));
  unordered_map_destroy(&map);

  assert.isNullptr("Unordered_map::unorderedMapDestroy data", map.data.data);
  for(int i = 0; i < BUCKETS; i++)
    assert.isNullptr("Unordered_map::unorderedMapDestroy bucket", map.buckets[i].data);
};







inline void Unordered_map::unorderedMapSetAndGet() {
  struct unordered_map map;
  unordered_map_init(&map, sizeof(int));

  const unsigned int additions = 20;
  const unsigned int string_size = 20;
  std::string keys[additions];

  for(int i = 0; i < additions; i++){
    keys[i] = randomString(string_size);
    unordered_map_set(&map, (char*)&i, keys[i].c_str());
  };

  for(int i = 0; i < additions; i++){
    int value = 0;
    unordered_map_get(&map, (char*)&value, keys[i].c_str());
    assert.equal("Unordered_map::unorderedMapSetAndGet", value, i);
  };

  unordered_map_destroy(&map);
};
};