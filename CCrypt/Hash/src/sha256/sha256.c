////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

// // delete conversion
//   uint32_t x = ((uint32_t)(uint8_t)data[0] << 24) |
//                 ((uint32_t)(uint8_t)data[1] << 16) |
//                 ((uint32_t)(uint8_t)data[2] << 8)  |
//                 ((uint32_t)(uint8_t)data[3]);






#include "sha256/sha256.h"
#include "sha256.h"

int K[7] = {4, 9, 25, 49, 121, 13*13, 17*17};





void crypt_sha256(char* data, char* hash) {
  // --- Step 1. Initial hash values
  char H[8][4] = {
    {0x6a, 0x09, 0xe6, 0x67},
    {0xbb, 0x67, 0xae, 0x85},
    {0x3c, 0x6e, 0xf3, 0x72},
    {0xa5, 0x4f, 0xf5, 0x3a},
    {0x51, 0x0e, 0x52, 0x7f},
    {0x9b, 0x05, 0x68, 0x8c},
    {0x1f, 0x83, 0xd9, 0xab},
    {0x5b, 0xe0, 0xcd, 0x19}
  };

  // --- Step 2. SHA-256 constants
  static const uint32_t K[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
  };

  // --- Step 3. Preprocessing (single 512-bit block)
  uint8_t msg[64] = {0};
  size_t len = strlen(data);
  if (len > 55) len = 55;
  memcpy(msg, data, len);
  msg[len] = 0x80;
  uint64_t bit_len = (uint64_t)len * 8;
  msg[63] = bit_len & 0xFF;
  msg[62] = (bit_len >> 8) & 0xFF;
  msg[61] = (bit_len >> 16) & 0xFF;
  msg[60] = (bit_len >> 24) & 0xFF;

  // --- Step 4. Message schedule W
  char W[64][4] = {{0}};
  for (int t = 0; t < 16; t++) {
    W[t][0] = msg[t * 4];
    W[t][1] = msg[t * 4 + 1];
    W[t][2] = msg[t * 4 + 2];
    W[t][3] = msg[t * 4 + 3];
  }

  for (int t = 16; t < 64; t++) {
    char s0[4], s1[4];

    // s0 = small sigma0
    char rot7[4], rot18[4];
    crypt_sha256_ROTR(W[t - 15], rot7, 7);
    crypt_sha256_ROTR(W[t - 15], rot18, 18);
    uint32_t w15 = ((uint32_t)(uint8_t)W[t - 15][0] << 24) |
                   ((uint32_t)(uint8_t)W[t - 15][1] << 16) |
                   ((uint32_t)(uint8_t)W[t - 15][2] << 8) |
                   (uint32_t)(uint8_t)W[t - 15][3];
    uint32_t shr3 = w15 >> 3;
    s0[0] = (rot7[0] ^ rot18[0] ^ ((shr3 >> 24) & 0xFF));
    s0[1] = (rot7[1] ^ rot18[1] ^ ((shr3 >> 16) & 0xFF));
    s0[2] = (rot7[2] ^ rot18[2] ^ ((shr3 >> 8) & 0xFF));
    s0[3] = (rot7[3] ^ rot18[3] ^ (shr3 & 0xFF));

    // s1 = small sigma1
    char rot17[4], rot19[4];
    crypt_sha256_ROTR(W[t - 2], rot17, 17);
    crypt_sha256_ROTR(W[t - 2], rot19, 19);
    uint32_t w2 = ((uint32_t)(uint8_t)W[t - 2][0] << 24) |
                  ((uint32_t)(uint8_t)W[t - 2][1] << 16) |
                  ((uint32_t)(uint8_t)W[t - 2][2] << 8) |
                  (uint32_t)(uint8_t)W[t - 2][3];
    uint32_t shr10 = w2 >> 10;
    s1[0] = (rot17[0] ^ rot19[0] ^ ((shr10 >> 24) & 0xFF));
    s1[1] = (rot17[1] ^ rot19[1] ^ ((shr10 >> 16) & 0xFF));
    s1[2] = (rot17[2] ^ rot19[2] ^ ((shr10 >> 8) & 0xFF));
    s1[3] = (rot17[3] ^ rot19[3] ^ (shr10 & 0xFF));

    uint32_t w16 = ((uint32_t)(uint8_t)W[t - 16][0] << 24) |
                   ((uint32_t)(uint8_t)W[t - 16][1] << 16) |
                   ((uint32_t)(uint8_t)W[t - 16][2] << 8) |
                   (uint32_t)(uint8_t)W[t - 16][3];
    uint32_t w7 = ((uint32_t)(uint8_t)W[t - 7][0] << 24) |
                  ((uint32_t)(uint8_t)W[t - 7][1] << 16) |
                  ((uint32_t)(uint8_t)W[t - 7][2] << 8) |
                  (uint32_t)(uint8_t)W[t - 7][3];
    uint32_t s0i = ((uint32_t)(uint8_t)s0[0] << 24) |
                   ((uint32_t)(uint8_t)s0[1] << 16) |
                   ((uint32_t)(uint8_t)s0[2] << 8) |
                   (uint32_t)(uint8_t)s0[3];
    uint32_t s1i = ((uint32_t)(uint8_t)s1[0] << 24) |
                   ((uint32_t)(uint8_t)s1[1] << 16) |
                   ((uint32_t)(uint8_t)s1[2] << 8) |
                   (uint32_t)(uint8_t)s1[3];

    uint32_t wt = w16 + s0i + w7 + s1i;
    W[t][0] = (wt >> 24) & 0xFF;
    W[t][1] = (wt >> 16) & 0xFF;
    W[t][2] = (wt >> 8) & 0xFF;
    W[t][3] = wt & 0xFF;
  }

  // --- Step 5. Initialize working vars
  char a[4], b[4], c[4], d[4], e[4], f[4], g[4], h[4];
  memcpy(a, H[0], 4);
  memcpy(b, H[1], 4);
  memcpy(c, H[2], 4);
  memcpy(d, H[3], 4);
  memcpy(e, H[4], 4);
  memcpy(f, H[5], 4);
  memcpy(g, H[6], 4);
  memcpy(h, H[7], 4);

  // --- Step 6. Main loop (uses helper functions)
  for (int t = 0; t < 64; t++) {
    char S1[4], ch[4], temp1[4], S0[4], maj[4];
    crypt_sha256_bigSigma1(e, S1);
    crypt_sha256_ch(e, f, g, ch);

    // temp1 = h + S1 + ch + K[t] + W[t]
    uint32_t ht = ((uint32_t)(uint8_t)h[0] << 24) |
                  ((uint32_t)(uint8_t)h[1] << 16) |
                  ((uint32_t)(uint8_t)h[2] << 8) |
                  (uint32_t)(uint8_t)h[3];
    uint32_t s1v = ((uint32_t)(uint8_t)S1[0] << 24) |
                   ((uint32_t)(uint8_t)S1[1] << 16) |
                   ((uint32_t)(uint8_t)S1[2] << 8) |
                   (uint32_t)(uint8_t)S1[3];
    uint32_t chv = ((uint32_t)(uint8_t)ch[0] << 24) |
                   ((uint32_t)(uint8_t)ch[1] << 16) |
                   ((uint32_t)(uint8_t)ch[2] << 8) |
                   (uint32_t)(uint8_t)ch[3];
    uint32_t wtv = ((uint32_t)(uint8_t)W[t][0] << 24) |
                   ((uint32_t)(uint8_t)W[t][1] << 16) |
                   ((uint32_t)(uint8_t)W[t][2] << 8) |
                   (uint32_t)(uint8_t)W[t][3];
    uint32_t temp1v = ht + s1v + chv + K[t] + wtv;
    temp1[0] = (temp1v >> 24) & 0xFF;
    temp1[1] = (temp1v >> 16) & 0xFF;
    temp1[2] = (temp1v >> 8) & 0xFF;
    temp1[3] = temp1v & 0xFF;

    crypt_sha256_bigSigma0(a, S0);
    crypt_sha256_maj(a, b, c, maj);

    uint32_t S0v = ((uint32_t)(uint8_t)S0[0] << 24) |
                   ((uint32_t)(uint8_t)S0[1] << 16) |
                   ((uint32_t)(uint8_t)S0[2] << 8) |
                   (uint32_t)(uint8_t)S0[3];
    uint32_t majv = ((uint32_t)(uint8_t)maj[0] << 24) |
                    ((uint32_t)(uint8_t)maj[1] << 16) |
                    ((uint32_t)(uint8_t)maj[2] << 8) |
                    (uint32_t)(uint8_t)maj[3];
    uint32_t temp2v = S0v + majv;

    // Update
    memcpy(h, g, 4);
    memcpy(g, f, 4);
    memcpy(f, e, 4);

    uint32_t ev = ((uint32_t)(uint8_t)e[0] << 24) |
                  ((uint32_t)(uint8_t)e[1] << 16) |
                  ((uint32_t)(uint8_t)e[2] << 8) |
                  (uint32_t)(uint8_t)e[3];
    uint32_t dv = ((uint32_t)(uint8_t)d[0] << 24) |
                  ((uint32_t)(uint8_t)d[1] << 16) |
                  ((uint32_t)(uint8_t)d[2] << 8) |
                  (uint32_t)(uint8_t)d[3];
    uint32_t newe = dv + temp1v;
    e[0] = (newe >> 24) & 0xFF;
    e[1] = (newe >> 16) & 0xFF;
    e[2] = (newe >> 8) & 0xFF;
    e[3] = newe & 0xFF;

    memcpy(d, c, 4);
    memcpy(c, b, 4);
    memcpy(b, a, 4);

    uint32_t av = ((uint32_t)(uint8_t)a[0] << 24) |
                  ((uint32_t)(uint8_t)a[1] << 16) |
                  ((uint32_t)(uint8_t)a[2] << 8) |
                  (uint32_t)(uint8_t)a[3];
    uint32_t newa = temp1v + temp2v;
    a[0] = (newa >> 24) & 0xFF;
    a[1] = (newa >> 16) & 0xFF;
    a[2] = (newa >> 8) & 0xFF;
    a[3] = newa & 0xFF;
  }

  // --- Step 7. Add results back into H
  for (int i = 0; i < 8; i++) {
    uint32_t hv = ((uint32_t)(uint8_t)H[i][0] << 24) |
                  ((uint32_t)(uint8_t)H[i][1] << 16) |
                  ((uint32_t)(uint8_t)H[i][2] << 8) |
                  (uint32_t)(uint8_t)H[i][3];
    uint32_t av;
    switch (i) {
      case 0: av = ((uint32_t)(uint8_t)a[0] << 24) | ((uint32_t)(uint8_t)a[1] << 16) | ((uint32_t)(uint8_t)a[2] << 8) | (uint32_t)(uint8_t)a[3]; break;
      case 1: av = ((uint32_t)(uint8_t)b[0] << 24) | ((uint32_t)(uint8_t)b[1] << 16) | ((uint32_t)(uint8_t)b[2] << 8) | (uint32_t)(uint8_t)b[3]; break;
      case 2: av = ((uint32_t)(uint8_t)c[0] << 24) | ((uint32_t)(uint8_t)c[1] << 16) | ((uint32_t)(uint8_t)c[2] << 8) | (uint32_t)(uint8_t)c[3]; break;
      case 3: av = ((uint32_t)(uint8_t)d[0] << 24) | ((uint32_t)(uint8_t)d[1] << 16) | ((uint32_t)(uint8_t)d[2] << 8) | (uint32_t)(uint8_t)d[3]; break;
      case 4: av = ((uint32_t)(uint8_t)e[0] << 24) | ((uint32_t)(uint8_t)e[1] << 16) | ((uint32_t)(uint8_t)e[2] << 8) | (uint32_t)(uint8_t)e[3]; break;
      case 5: av = ((uint32_t)(uint8_t)f[0] << 24) | ((uint32_t)(uint8_t)f[1] << 16) | ((uint32_t)(uint8_t)f[2] << 8) | (uint32_t)(uint8_t)f[3]; break;
      case 6: av = ((uint32_t)(uint8_t)g[0] << 24) | ((uint32_t)(uint8_t)g[1] << 16) | ((uint32_t)(uint8_t)g[2] << 8) | (uint32_t)(uint8_t)g[3]; break;
      case 7: av = ((uint32_t)(uint8_t)h[0] << 24) | ((uint32_t)(uint8_t)h[1] << 16) | ((uint32_t)(uint8_t)h[2] << 8) | (uint32_t)(uint8_t)h[3]; break;
    }
    uint32_t sum = hv + av;
    H[i][0] = (sum >> 24) & 0xFF;
    H[i][1] = (sum >> 16) & 0xFF;
    H[i][2] = (sum >> 8) & 0xFF;
    H[i][3] = sum & 0xFF;
  }

  // --- Step 8. Output digest
  for (int i = 0; i < 8; i++) {
    hash[i * 4 + 0] = H[i][0];
    hash[i * 4 + 1] = H[i][1];
    hash[i * 4 + 2] = H[i][2];
    hash[i * 4 + 3] = H[i][3];
  }
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
};






void crypt_sha256_bigSigma0(char data[4], char out[4]) {
  char r1[4] = {0};
  char r2[4] = {0};
  char r3[4] = {0};

  crypt_sha256_ROTR(data, r1, 2);
  crypt_sha256_ROTR(data, r2, 13);
  crypt_sha256_ROTR(data, r3, 22);

  uint32_t r1_x = ((uint32_t)(uint8_t)r1[0] << 24) |
                  ((uint32_t)(uint8_t)r1[1] << 16) |
                  ((uint32_t)(uint8_t)r1[2] << 8)  |
                  ((uint32_t)(uint8_t)r1[3]);

  uint32_t r2_x = ((uint32_t)(uint8_t)r2[0] << 24) |
                  ((uint32_t)(uint8_t)r2[1] << 16) |
                  ((uint32_t)(uint8_t)r2[2] << 8)  |
                  ((uint32_t)(uint8_t)r2[3]);

  uint32_t r3_x = ((uint32_t)(uint8_t)r3[0] << 24) |
                  ((uint32_t)(uint8_t)r3[1] << 16) |
                  ((uint32_t)(uint8_t)r3[2] << 8)  |
                  ((uint32_t)(uint8_t)r3[3]);

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

  uint32_t r1_x = ((uint32_t)(uint8_t)r1[0] << 24) |
                  ((uint32_t)(uint8_t)r1[1] << 16) |
                  ((uint32_t)(uint8_t)r1[2] << 8)  |
                  ((uint32_t)(uint8_t)r1[3]);

  uint32_t r2_x = ((uint32_t)(uint8_t)r2[0] << 24) |
                  ((uint32_t)(uint8_t)r2[1] << 16) |
                  ((uint32_t)(uint8_t)r2[2] << 8)  |
                  ((uint32_t)(uint8_t)r2[3]);

  uint32_t r3_x = ((uint32_t)(uint8_t)r3[0] << 24) |
                  ((uint32_t)(uint8_t)r3[1] << 16) |
                  ((uint32_t)(uint8_t)r3[2] << 8)  |
                  ((uint32_t)(uint8_t)r3[3]);

  uint32_t o_x = r1_x ^ r2_x ^ r3_x;

  out[0] = (o_x >> 24) & 0xFF;
  out[1] = (o_x >> 16) & 0xFF;
  out[2] = (o_x >> 8)  & 0xFF;
  out[3] =  o_x & 0xFF;
}






void crypt_sha256_ch(char x[4], char y[4], char z[4], char out[4]) {
  uint32_t rx = ((uint32_t)(uint8_t)x[0] << 24) |
                  ((uint32_t)(uint8_t)x[1] << 16) |
                  ((uint32_t)(uint8_t)x[2] << 8)  |
                  ((uint32_t)(uint8_t)x[3]);

  uint32_t ry = ((uint32_t)(uint8_t)y[0] << 24) |
                  ((uint32_t)(uint8_t)y[1] << 16) |
                  ((uint32_t)(uint8_t)y[2] << 8)  |
                  ((uint32_t)(uint8_t)y[3]);

  uint32_t rz = ((uint32_t)(uint8_t)z[0] << 24) |
                  ((uint32_t)(uint8_t)z[1] << 16) |
                  ((uint32_t)(uint8_t)z[2] << 8)  |
                  ((uint32_t)(uint8_t)z[3]);

  uint32_t o_x = (rx & ry) ^ ((~rx) & rz);

  out[0] = (o_x >> 24) & 0xFF;
  out[1] = (o_x >> 16) & 0xFF;
  out[2] = (o_x >> 8)  & 0xFF;
  out[3] =  o_x & 0xFF;
}






void crypt_sha256_maj(char x[4], char y[4], char z[4], char out[4]) {
  uint32_t rx = ((uint32_t)(uint8_t)x[0] << 24) |
                  ((uint32_t)(uint8_t)x[1] << 16) |
                  ((uint32_t)(uint8_t)x[2] << 8)  |
                  ((uint32_t)(uint8_t)x[3]);

  uint32_t ry = ((uint32_t)(uint8_t)y[0] << 24) |
                  ((uint32_t)(uint8_t)y[1] << 16) |
                  ((uint32_t)(uint8_t)y[2] << 8)  |
                  ((uint32_t)(uint8_t)y[3]);

  uint32_t rz = ((uint32_t)(uint8_t)z[0] << 24) |
                  ((uint32_t)(uint8_t)z[1] << 16) |
                  ((uint32_t)(uint8_t)z[2] << 8)  |
                  ((uint32_t)(uint8_t)z[3]);

  uint32_t o_x = (rx & ry) ^ (rx & rz) ^ (ry & rz);

  out[0] = (o_x >> 24) & 0xFF;
  out[1] = (o_x >> 16) & 0xFF;
  out[2] = (o_x >> 8)  & 0xFF;
  out[3] =  o_x & 0xFF;
};
