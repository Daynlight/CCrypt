#pragma once
#include <stdio.h>
#include <string>
#include <functional>

namespace UnitTests{
class Assert{
private:
  unsigned int total = 0;
  unsigned int passed = 0;

public:
  template<typename T>
  void assertion(const std::string& assertText, std::function<bool()> fun){
    total++;

    if(!fun)
      printf("%s\n", assertText.c_str());
    else
      passed++;
  };

  void results(){
    printf("%d/%d passed\n", passed, total);
  };
};
};
