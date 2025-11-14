//////////////////////////
///////// vector /////////
//////////////////////////
//// IDEA ////
// A vector is a dynamic array that can grow when needed.
// It lets us store data even when we don't know how many elements we will need.
// Useful for unordered_map, paths, lists, and more.

//// How it works: ////
// A vector keeps two numbers:
//   * size     — how many elements are currently stored
//   * capacity — how much space is allocated
//
// When adding elements:
//   * If size < capacity, we just insert the new element.
//   * If size == capacity, we need more room:
//       - allocate a new larger buffer
//       - copy all existing elements to it
//       - free the old buffer
//       - replace it with the new one
//
// This allows the vector to grow dynamically
// as long as the system has memory available.

//// TL;TR ////
// * When capacity is full, allocate a larger buffer,
//   copy elements, and continue using the new one.


#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif



struct vector{
  unsigned int cap;
  unsigned int size;
  unsigned int size_of_el;
  char* data;
};

void vector_init(struct vector* vector, unsigned int size_of_el);
void vector_destroy(struct vector* vector);

void vector_resize(struct vector* vector);
void vector_reserve(struct vector* vector, unsigned int cap);

void vector_emplace_back(struct vector* vector, char* data);

void vector_get(struct vector* vector, char* out, unsigned int index);
void vector_set(struct vector* vector, char* data, unsigned int index);



#ifdef __cplusplus
}
#endif

#endif