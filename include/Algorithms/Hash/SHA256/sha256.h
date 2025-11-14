//////////////////////////
///////// sha256 /////////
//////////////////////////
//// IDEA ////
// SHA-256 is a one-way hashing method.
// Once data is hashed, nobody can reverse it.
// Used for password hashing, integrity checks,
// and cryptographic key operations.

//// How it works: ////
// The input is padded: first a '1' bit, then zeros,
// and finally the message length (64 bits).
// The padded message is split into 512-bit blocks.
//
// For each block:
//   * Create a 64-word message schedule (W[0..63])
//   * Initialize 8 working variables (a..h) with H0..H7
//   * Run 64 rounds using ROTR, Σ0, Σ1, CH, Maj,
//     and 64 constant values derived from prime numbers
//   * Add the results back into H0..H7
//
// If the message has more blocks, repeat.

//// TL;TR ////
// * Pad message and split into 512-bit blocks
// * For each block, run 64 rounds of mixing
// * Final H0..H7 values form the 256-bit hash


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
};
#endif


#endif