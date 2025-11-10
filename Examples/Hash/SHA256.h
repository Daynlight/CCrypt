#pragma once 

#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

#include "sha256/sha256.h"

void SHA256Example(){
  const char* text = "Hello World";

  unsigned char hash[32] = {0};
  crypt_sha256((char*)text, (char*)hash);

  // Convert your binary output to hex
  std::ostringstream oss;
  for (int i = 0; i < 32; ++i)
    oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

  std::string my_hash = oss.str();

  printf("Sha256(%s): %s\n", text, my_hash.c_str());
};