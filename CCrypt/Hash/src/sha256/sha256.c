#include "sha256/sha256.h"
#include "sha256.h"

int K[7] = {4, 9, 25, 49, 121, 13*13, 17*17};

void crypt_sha256(char* data, char* hash){
  hash[0] = 'a';
};

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

void crypt_sha256_bigSigma0(char data[4], char out[4]) {
  char r1[4] = {0};
  char r2[4] = {0};
  char r3[4] = {0};

  crypt_sha256_ROTR(data, r1, 2);
  crypt_sha256_ROTR(data, r2, 13);
  crypt_sha256_ROTR(data, r3, 22);

  uint32_t r1_x = ((uint32_t)(uint8_t)data[0] << 24) |
              ((uint32_t)(uint8_t)data[1] << 16) |
              ((uint32_t)(uint8_t)data[2] << 8)  |
              ((uint32_t)(uint8_t)data[3]);

  uint32_t r2_x = ((uint32_t)(uint8_t)data[0] << 24) |
            ((uint32_t)(uint8_t)data[1] << 16) |
            ((uint32_t)(uint8_t)data[2] << 8)  |
            ((uint32_t)(uint8_t)data[3]);

  uint32_t r3_x = ((uint32_t)(uint8_t)data[0] << 24) |
            ((uint32_t)(uint8_t)data[1] << 16) |
            ((uint32_t)(uint8_t)data[2] << 8)  |
            ((uint32_t)(uint8_t)data[3]);

  uint32_t o_x = r1_x ^ r2_x ^ r3_x;

  out[0] = (o_x >> 24) & 0xFF;
  out[1] = (o_x >> 16) & 0xFF;
  out[2] = (o_x >> 8)  & 0xFF;
  out[3] =  o_x & 0xFF;
};

void crypt_sha256_bigSigma1(char data[4], char out[4]){
  char r1[4] = {0};
  char r2[4] = {0};
  char r3[4] = {0};

  crypt_sha256_ROTR(data, r1, 6);
  crypt_sha256_ROTR(data, r2, 11);
  crypt_sha256_ROTR(data, r3, 25);

  uint32_t r1_x = ((uint32_t)(uint8_t)data[0] << 24) |
              ((uint32_t)(uint8_t)data[1] << 16) |
              ((uint32_t)(uint8_t)data[2] << 8)  |
              ((uint32_t)(uint8_t)data[3]);

  uint32_t r2_x = ((uint32_t)(uint8_t)data[0] << 24) |
            ((uint32_t)(uint8_t)data[1] << 16) |
            ((uint32_t)(uint8_t)data[2] << 8)  |
            ((uint32_t)(uint8_t)data[3]);

  uint32_t r3_x = ((uint32_t)(uint8_t)data[0] << 24) |
            ((uint32_t)(uint8_t)data[1] << 16) |
            ((uint32_t)(uint8_t)data[2] << 8)  |
            ((uint32_t)(uint8_t)data[3]);

  uint32_t o_x = r1_x ^ r2_x ^ r3_x;

  out[0] = (o_x >> 24) & 0xFF;
  out[1] = (o_x >> 16) & 0xFF;
  out[2] = (o_x >> 8)  & 0xFF;
  out[3] =  o_x & 0xFF;
};
