#ifndef SHA256_H
#define SHA256_H

#include <string.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

void crypt_sha256_ROTR(char data[4], char out[4], unsigned int k);
void crypt_sha256(char* data, char* hash);


#ifdef __cplusplus
}
#endif

#endif