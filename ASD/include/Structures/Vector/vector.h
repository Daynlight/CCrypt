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



#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct vector{
  unsigned int cap;
  unsigned int size;
  unsigned int size_of_el;
  char* data;
};

void vector_init(struct vector* vector, unsigned int size_of_el){
  vector->size_of_el = size_of_el;
  vector->data = (char*)calloc(1, vector->size_of_el);
  vector->cap = 1;
  vector->size = 0;
};

void vector_destroy(struct vector* vector){
  free(vector->data);
};

void vector_resize(struct vector* vector) {
  unsigned int new_cap = vector->cap * 2 + 1; 
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};

void vector_emplace_back(struct vector* vector, char* data){
  if(vector->size >= vector->cap)
    vector_resize(vector);
  
  memcpy(vector->data + vector->size * vector->size_of_el, data, vector->size_of_el);
  vector->size++;
};

void vector_get(struct vector* vector, char* out, unsigned int index){
  if(index >= vector->size) {
    fprintf(stderr, "vector_get error: index %u out of range (size=%u)\n",
            index, vector->size);
    return;
  };
  unsigned int offset = index * vector->size_of_el;
  memcpy(out, vector->data + offset, vector->size_of_el);
};

void vector_set(struct vector* vector, char* data, unsigned int index){
  if(index >= vector->size) {
    fprintf(stderr, "vector_set error: index %u out of range (size=%u)\n",
            index, vector->size);
    return;
  };
  unsigned int offset = index * vector->size_of_el;
  memcpy(vector->data + offset, data, vector->size_of_el);
};
