#include "Structures/Unordered_map/unordered_map.h"






unsigned int unordered_map_hash_fun(const char* key){
  unsigned char hash[32] = {0};
  crypt_sha256((char*)key, (char*)hash);

  unsigned int result = 0;
  for (int i = 0; i < 4; ++i)
      result = (result << 8) | hash[i];

  return result;
};






void unordered_map_init(struct unordered_map* unordered_map, unsigned int size_of_el){
  vector_init(&unordered_map->data, size_of_el);
  for(int i = 0; i < BUCKETS; i++)
    vector_init(&unordered_map->buckets[i], sizeof(struct bucket_record));
};

void unordered_map_destroy(struct unordered_map* unordered_map){
  vector_destroy(&unordered_map->data);
  for(int i = 0; i < BUCKETS; i++)
    vector_destroy(&unordered_map->buckets[i]);
};






int unordered_map_get(struct unordered_map* unordered_map, char* out, const char* key){
  unsigned int hash = unordered_map_hash_fun(key);
  unsigned int bucket_id = hash % BUCKETS;

  unsigned int index = 0;
  for(int i = 0; i < unordered_map->buckets[bucket_id].size; i++){    // look for key in bucket
    index = i;
    
    struct bucket_record record;
    vector_get(&unordered_map->buckets[bucket_id], (char*)&record, i);

    if(strcmp(record.key, key) == 0)
      break;
    else
      index++;
  }

  if(index >= unordered_map->buckets[bucket_id].size){  // don't found
    return -1;
  }
  else{                                                     // found
    struct bucket_record record;
    vector_get(&unordered_map->buckets[bucket_id], (char*)&record, index);
    vector_get(&unordered_map->data, out, record.index);
  };
  return 0;
};






void unordered_map_set(struct unordered_map* unordered_map, char* data, const char* key){
  unsigned int hash = unordered_map_hash_fun(key);
  unsigned int bucket_id = hash % BUCKETS;

  unsigned int index = 0;
  for(int i = 0; i < unordered_map->buckets[bucket_id].size; i++){    // look for key in bucket
    index = i;
    
    struct bucket_record record;
    vector_get(&unordered_map->buckets[bucket_id], (char*)&record, i);

    if(strcmp(record.key, key) == 0)
      break;
    else
      index++;
  }

  if(index >= unordered_map->buckets[bucket_id].size){  // don't found
    struct bucket_record record;
    record.index = unordered_map->data.size;
    memcpy(record.key, key, KEYSIZE);
    vector_emplace_back(&unordered_map->buckets[bucket_id], (char*)&record);
    vector_emplace_back(&unordered_map->data, data);
  }
  else{                                                     // found
    vector_set(&unordered_map->data, data, index);
  };
};