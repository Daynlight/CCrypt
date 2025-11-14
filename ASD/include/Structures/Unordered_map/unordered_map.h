/////////////////////////
///// unordered_map /////
/////////////////////////
//// IDEA ////
// We want a fast way to find the value from a kay.
// An unordered_map gives O(1) average lookup time,
// so it is fast to finding values from keys.

//// How it works: ////
// In our implementation we keep the actual data in a main vector.
//
// To avoid searching through the whole vector,
// we use a hash table made of buckets.
// A bucket is a small vector that stores:
//   - the key (command name)
//   - the index pointing to the real data
//
// When we insert or search:
//   * We compute the hash of the key
//   * We take (hash % BUCKETS) to choose the bucket
//    * We only search inside that one bucket
//    * We add value to that one bucket with index
//
// A good hash function spreads keys evenly,
// so buckets stay small and lookups are fast.
// More buckets means fewer collisions,
// at the cost of more memory.

//// TL;TR ////
// * We hash the key to select a bucket
// * We store (key, index) in that bucket
// * Lookup only scans one bucket, not all data


#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H


#include "Structures/Vector/vector.h"
#include "Algorithms/Hash/SHA256/sha256.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#ifndef KEYSIZE
  #define KEYSIZE 32
#endif
#ifndef BUCKETS
  #define BUCKETS 10
#endif


#ifdef __cplusplus
extern "C" {
#endif



struct bucket_record{
  char key[KEYSIZE];                  // key
  unsigned int index;                 // localization
};

struct unordered_map{
  struct vector data;                 // real data
  struct vector buckets[BUCKETS];     // type of bucket_record
};


unsigned int unordered_map_hash_fun(const char* key);

void unordered_map_init(struct unordered_map* unordered_map, unsigned int size_of_el);
void unordered_map_destroy(struct unordered_map* unordered_map);

int unordered_map_get(struct unordered_map* unordered_map, char* out, const char* key);
void unordered_map_set(struct unordered_map* unordered_map, char* data, const char* key);



#ifdef __cplusplus
}
#endif

#endif