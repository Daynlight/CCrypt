#ifndef SHA256_H
#define SHA256_H

#include <string.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif



void crypt_sha256(char* data, char* hash);

void crypt_sha256_ROTR(char data[4], char out[4], unsigned int k);

void crypt_sha256_bigSigma0(char data[4], char out[4]);
void crypt_sha256_bigSigma1(char data[4], char out[4]);

void crypt_sha256_ch(char x[4], char y[4], char z[4], char out[4]);
void crypt_sha256_maj(char x[4], char y[4], char z[4], char out[4]);



#ifdef __cplusplus
}
#endif

#endif