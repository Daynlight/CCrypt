#pragma once

#include "../../Assert.h"

#include "Algorithms/Hash/SHA256/sha256.h"

#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <cstring>

namespace UnitTests{

std::string cpp_sha(const std::string& text) {
  unsigned char hash[SHA256_DIGEST_LENGTH];

  // Compute SHA-256 (OpenSSL)
  ::SHA256(reinterpret_cast<const unsigned char*>(text.c_str()), text.size(), hash);

  // Convert binary hash to hex string
  std::ostringstream oss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
      oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

  return oss.str();
};













class SHA256{
private:
  Assert assert;
public:
  bool runAll();

  void ROTR();
  void notROTR();
  
  void bigSigma0();
  void notBigSigma0();

  void bigSigma1();
  void notBigSigma1();
  
  void Ch();
  void notCh();

  void Maj();
  void notMaj();

  void compareWithCPPSHA256();
};

bool UnitTests::SHA256::runAll(){
  ROTR();
  notROTR();
  bigSigma0();
  notBigSigma0();
  bigSigma1();
  notBigSigma1();
  Ch();
  notCh();
  Maj();
  notMaj();
  compareWithCPPSHA256();

  return assert.results("SHA256");
};













inline void SHA256::ROTR(){
  char text[4] = {0x48, 0x65, 0x6C, 0x6C};
  char rot_text[4] = {0};
  crypt_sha256_ROTR(text, rot_text, 2);
  unsigned char expected[4] = {0x12, 0x19, 0x5B, 0x1B};
  
  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if(rot_text[i] != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::ROTR failed", passed);
  
  if(!passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", rot_text[j] & 0xFF, expected[j]);
  };
};







inline void SHA256::notROTR(){
  char text[4] = {0x48, 0x65, 0x6C, 0x6C};
  char rot_text[4] = {0};
  crypt_sha256_ROTR(text, rot_text, 2);
  unsigned char expected[4] = {0x12, 0x19, 0x5B, 0x1C};
  
  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if(rot_text[i] != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::ROTR failed", !passed);
  
  if(passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", rot_text[j] & 0xFF, expected[j]);
  };
};







inline void SHA256::bigSigma0() {
  char text[4] = {0x48, 0x65, 0x6C, 0x6C};
  char sig_text[4] = {0};
  crypt_sha256_bigSigma0(text, sig_text);
  unsigned char expected[4] = {0xE4, 0xCA, 0xA9, 0x11};

  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if((unsigned char)(sig_text[i]) != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::bigSigma0 failed", passed);
  
  if(!passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", (unsigned char)(sig_text[j]), expected[j]);
  };
};







inline void SHA256::notBigSigma0() {
  char text[4] = {0x48, 0x65, 0x6C, 0x6C};
  char sig_text[4] = {0};
  crypt_sha256_bigSigma0(text, sig_text);
  unsigned char expected[4] = {0x14, 0xAA, 0x49, 0x21};

  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if((unsigned char)(sig_text[i]) != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::bigSigma0 failed", !passed);
  
  if(passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", (unsigned char)(sig_text[j]), expected[j]);
  };
};







inline void SHA256::bigSigma1() {
  char text[4] = {0x48, 0x65, 0x6C, 0x6C};
  char sig_text[4] = {0};
  crypt_sha256_bigSigma1(text, sig_text);
  unsigned char expected[4] = {0x0E, 0x1E, 0xAF, 0x38};

  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if((unsigned char)(sig_text[i]) != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::bigSigma1 failed", passed);
  
  if(!passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", (unsigned char)(sig_text[j]), expected[j]);
  };
};







inline void SHA256::notBigSigma1() {
  char text[4] = {0x48, 0x65, 0x6C, 0x6C};
  char sig_text[4] = {0};
  crypt_sha256_bigSigma1(text, sig_text);
  unsigned char expected[4] = {0x5E, 0xFE, 0x6F, 0x21};

  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if((unsigned char)(sig_text[i]) != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::notBigSigma1 failed", !passed);
  
  if(passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", (unsigned char)(sig_text[j]), expected[j]);
  };
}







inline void SHA256::Ch(){
  char text1[4] = {0x48, 0x65, 0x6C, 0x6C};
  char text2[4] = {0x41, 0x21, 0x7E, 0x4F};
  char text3[4] = {0x0A, 0x43, 0x3C, 0x12};
  char sig_text[4] = {0};
  crypt_sha256_ch(text1, text2, text3, sig_text);
  unsigned char expected[4] = {0x42, 0x23, 0x7C, 0x5E};

  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if((unsigned char)(sig_text[i]) != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::Ch failed", passed);
  
  if(!passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", (unsigned char)(sig_text[j]), expected[j]);
  };
}







inline void SHA256::notCh(){
  char text1[4] = {0x48, 0x65, 0x6C, 0x6C};
  char text2[4] = {0x41, 0x21, 0x7E, 0x4F};
  char text3[4] = {0x0A, 0x43, 0x3C, 0x12};
  char sig_text[4] = {0};
  crypt_sha256_ch(text1, text2, text3, sig_text);
  unsigned char expected[4] = {0x12, 0x5B, 0x7A, 0x2D};

  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if((unsigned char)(sig_text[i]) != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::notCh failed", !passed);
  
  if(passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", (unsigned char)(sig_text[j]), expected[j]);
  };
}







inline void SHA256::Maj(){
  char text1[4] = {0x48, 0x65, 0x6C, 0x6C};
  char text2[4] = {0x41, 0x21, 0x7E, 0x4F};
  char text3[4] = {0x0A, 0x43, 0x3C, 0x12};
  char sig_text[4] = {0};
  crypt_sha256_maj(text1, text2, text3, sig_text);
  unsigned char expected[4] = {0x48, 0x61, 0x7C, 0x4E};

  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if((unsigned char)(sig_text[i]) != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::Ch failed", passed);
  
  if(!passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", (unsigned char)(sig_text[j]), expected[j]);
  };
}







inline void SHA256::notMaj(){
  char text1[4] = {0x48, 0x65, 0x6C, 0x6C};
  char text2[4] = {0x41, 0x21, 0x7E, 0x4F};
  char text3[4] = {0x0A, 0x43, 0x3C, 0x12};
  char sig_text[4] = {0};
  crypt_sha256_maj(text1, text2, text3, sig_text);
  unsigned char expected[4] = {0x24, 0x32, 0x7A, 0x1D};

  bool passed = 1;
  for(int i = 0; i < 4; i++)
    if((unsigned char)(sig_text[i]) != expected[i]){
      passed = 0;
      break;
    };

  assert.assertion("Sha256::Ch failed", !passed);
  
  if(passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", (unsigned char)(sig_text[j]), expected[j]);
  };
}






inline void SHA256::compareWithCPPSHA256() {
  const char* text = "Hello World";
  const std::string cpp_hash = cpp_sha(text);

  unsigned char hash[32] = {0};
  crypt_sha256((char*)text, (char*)hash);

  // Convert your binary output to hex
  std::ostringstream oss;
  for (int i = 0; i < 32; ++i)
    oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

  std::string my_hash = oss.str();

  bool passed = (cpp_hash == my_hash);
  assert.assertion("Sha256: compareWithCPPSHA256 failed", passed);

  if (!passed) {
    printf("\nTested : %s\n", my_hash.c_str());
    printf("Correct: %s\n", cpp_hash.c_str());
  }
};
};