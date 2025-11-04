#include "sha256/sha256.h"

int K[7] = {4, 9, 25, 49, 121, 13*13, 17*17, 21*21};

char* T1(char* data);
char* T2(char* data);
char* BigSigma0(char* data);
char* BigSigma1(char* data);
char* Ch(char* x, char* y, char* z);
char* Maj(char* x, char* y, char* z);

char* ROTR2(char* data);
char* ROTR13(char* data);
char* ROTR22(char* data);
char* ROTR6(char* data);
char* ROTR11(char* data);
char* ROTR25(char* data);

void crypt_sha256(char* data, char* hash){
  hash[0] = 'a';
}

void crypt_sha256_ROTR(char data[4], char out[4], unsigned int k) {
  uint32_t x = ((uint32_t)(uint8_t)data[0] << 24) |
                ((uint32_t)(uint8_t)data[1] << 16) |
                ((uint32_t)(uint8_t)data[2] << 8)  |
                ((uint32_t)(uint8_t)data[3]);

  uint32_t rot = (x >> k) | (x << (32 - k));

  out[0] = (rot >> 24) & 0xFF;
  out[1] = (rot >> 16) & 0xFF;
  out[2] = (rot >> 8)  & 0xFF;
  out[3] = rot & 0xFF;
}
