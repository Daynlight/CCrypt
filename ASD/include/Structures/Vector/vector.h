//////////////////////////
///////// vector /////////
//////////////////////////
//// IDEA ////
// Vector is dynamic array that allows 
// storing dynamic data that can change with time
// We want it for unordered_map, path, etc.

//// How it works: ////
// We have data and we don't know how much we have left
// We add element as long as we have space
// If we use all of our space we just create next 
// bigger buffer and copy data to them. After that
// we delete old buffer and swap with new one.
// In this way we have unlimited memory to use.

//// TL;TR ////
// * When we use all of space we have just create new bigger want and swap them

//// Optimization: ////
// * [NOTE] reserve function


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