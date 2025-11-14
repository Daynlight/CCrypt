/////////////////////////
///// unordered_map /////
/////////////////////////
//// IDEA ////
// We want fast way to find path from command
// unordered_map allow us to make fast lookup
// soo it is prefect structure to use

//// How it works: ////
// First we create vector with our real data
// in this case paths to commands
// Now to find path from command we have to 
// iterate through them.
// We will store additional informations in
// buckets. Bucket is vector where we store 
// keys and index to data in our main data
// vector. Now we add hash function when we
// want to find data instead of iterate
// through all of them we hash key and 
// make modulo BUCKETS to find bucket
// where key is stored. Hashing always
// gives the same results soo for the
// same name we always access the same bucket
// Instead of iterate for every element we
// iterate only in one bucket.
// More buckets = less iterations.
// Also quality of hash is important
// if hash is good then we separate keys in
// better way and we have less iteration to do.

//// TL;TR ////
// * We hash key and save them with index to real data in bucket
// * When we search for them we only search in one bucket


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