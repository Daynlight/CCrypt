#pragma once
#include "../Assert.h"

#include "sha256/sha256.h"

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
  Assert* assert;
public:
  SHA256(Assert* assert) :assert(assert) {};
  void runAll();
  void ROTR();
  void notROTR();
  void compareWithCPPSHA256();
};

void UnitTests::SHA256::runAll(){
  ROTR();
  notROTR();
  compareWithCPPSHA256();
}







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

  assert->assertion("Sha256: ROTR failed", passed);
  
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

  assert->assertion("Sha256: ROTR failed", !passed);
  
  if(passed){
    for(int j = 0; j < 4; j++)
      printf("%02X = %02X\n", rot_text[j] & 0xFF, expected[j]);
  };
};



inline void SHA256::compareWithCPPSHA256() {
  char text[50] = "Hello World";
  const std::string cpp_hash = cpp_sha(text);
  char hash[50] = {0};
  crypt_sha256(text, hash);

  assert->equal("Sha256: compareWithCPPSHA256 failed", hash, cpp_hash);
};
};