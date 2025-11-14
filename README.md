# ASD
Simple and Advanced data Structures and Algorithms written in C. Contains basic and advanced data structures, cryptography.


## TOC
- [TOC](#toc)
- [Library Usage](#library-usage)
  - [Option 1 (CMake)](#option-1-cmake)
  - [Option 2 (release lib)](#option-2-release-lib)
- [Algorithms](#algorithms)
  - [SHA256](#sha256)
    - [About](#about)
    - [How it works:](#how-it-works)
    - [TL;TR](#tltr)
    - [Usage](#usage)
- [Structures](#structures)
  - [Vector](#vector)
    - [About](#about-1)
    - [How it works:](#how-it-works-1)
    - [When adding elements:](#when-adding-elements)
    - [TL;TR](#tltr-1)
    - [Usage](#usage-1)
  - [Unordered\_map](#unordered_map)
    - [About](#about-2)
    - [How it works:](#how-it-works-2)
    - [A bucket](#a-bucket)
    - [When we insert or search:](#when-we-insert-or-search)
    - [TL;TR](#tltr-2)
    - [Usage](#usage-2)


## Library Usage
### Option 1 (CMake)
1. add repository as submodule
```bash
  git submodule add https://github.com/daynlight/ASD <path>
```
2. add subdirectory in your cmake and add lib to your project
```cmake
add_subdirectory(<path>)
target_link_libraries(<YourProject> PUBLIC ASD)
```

### Option 2 (release lib)
1. Download tag or data from [release branch](https://github.com/Daynlight/ASD/tree/release)
2. Link static lib
3. Include directories form ```include/```



## Algorithms
### SHA256
#### About
SHA-256 is a one-way hashing method.
Once data is hashed, nobody can reverse it.
Used for password hashing, integrity checks,
and cryptographic key operations.

#### How it works:
The input is padded: first a '1' bit, then zeros, and finally the message length (64 bits). The padded message is split into 512-bit blocks.

For each block:
  * Create a 64-word message schedule (W[0..63])
  * Initialize 8 working variables (a..h) with H0..H7
  * Run 64 rounds using ROTR, Σ0, Σ1, CH, Maj, and 64 constant values derived from prime numbers
  * Add the results back into H0..H7

If the message has more blocks, repeat.

#### TL;TR
* Pad message and split into 512-bit blocks
* For each block, run 64 rounds of mixing
* Final H0..H7 values form the 256-bit hash

#### Usage
```cpp
const char* text = "Hello World";
unsigned char hash[32] = {0};
crypt_sha256((char*)text, (char*)hash);   // hash data
```



## Structures
### Vector
#### About
A vector is a dynamic array that can grow when needed. It lets us store data even when we don't know how many elements we will need. Useful for unordered_map, paths, lists, and more.

#### How it works:
A vector keeps two numbers:
  * size     — how many elements are currently stored
  * capacity — how much space is allocated

#### When adding elements:
* If size < capacity, we just insert the new element.
* If size == capacity, we need more room:
  - allocate a new larger buffer
  - copy all existing elements to it
  - free the old buffer
  - replace it with the new one

This allows the vector to grow dynamically
as long as the system has memory available.

#### TL;TR
* When capacity is full, allocate a larger buffer, copy elements, and continue using the new one.

#### Usage
```cpp
struct vector vec;
vector_init(&vec, sizeof(int));           // initialize vector
vector_reserve(&vec, 10);                 // reserve data

int data = 5;
vector_emplace_back(&vec, (char*)&data);  // emplace data

int set = 3;
vector_set(&vec, (char*)&set, 0);         // set data at 0

int get = 0;
vector_get(&vec, (char*)&get, 0);         // get data at 0
printf("%d == %d\n", get, set);

vector_destroy(&vec);                     // destroy vector
```

### Unordered_map
#### About
We want a fast way to find the value from a kay. An unordered_map gives O(1) average lookup time, so it is fast to finding values from keys.

#### How it works:
In our implementation we keep the actual data in a main vector. To avoid searching through the whole vector, we use a hash table made of buckets.

#### A bucket 
Bucket is a small vector that stores:
  - the key (command name)
  - the index pointing to the real data

#### When we insert or search:
  * We compute the hash of the key
  * We take (hash % BUCKETS) to choose the bucket
  * We only search inside that one bucket
  * We add value to that one bucket with index

A good hash function spreads keys evenly, so buckets stay small and lookups are fast. More buckets means fewer collisions, at the cost of more memory.

#### TL;TR
  * We hash the key to select a bucket
  * We store (key, index) in that bucket
  * Lookup only scans one bucket, not all data

#### Usage
```cpp
struct unordered_map map;
unordered_map_init(&map, sizeof(int));    // initialize unordered_map

int a = 2;
unordered_map_set(&map, (char*)&a, "a");  // set data at "a"

int b = 0;
unordered_map_get(&map, (char*)&b, "a");  // get data at "a"

printf("%d = %d\n", a, b);

unordered_map_destroy(&map);              // destroy unordered_map
```
