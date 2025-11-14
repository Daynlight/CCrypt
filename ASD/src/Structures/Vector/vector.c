#include "Structures/Vector/vector.h"






void vector_init(struct vector* vector, unsigned int size_of_el){
  vector->size_of_el = size_of_el;
  vector->data = (char*)calloc(1, vector->size_of_el);
  vector->cap = 1;
  vector->size = 0;
};






void vector_destroy(struct vector* vector){
  free(vector->data);
  vector->data = NULL;
};






void vector_resize(struct vector* vector) {
  unsigned int new_cap = vector->cap * 2 + 1; 
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};






void vector_reserve(struct vector *vector, unsigned int cap){
  unsigned int new_cap = vector->cap + cap; 
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};






void vector_emplace_back(struct vector *vector, char *data){
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






void vector_alloc(struct vector *vector, unsigned int size, char *data){
  unsigned int missing_space = 2 * vector->size + size - vector->cap;
  vector_reserve(vector, missing_space);
  for(int i = 0; i < size; i++)
    vector_emplace_back(vector, data);
};
