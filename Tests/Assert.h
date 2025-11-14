#pragma once
#include <stdio.h>
#include <string>
#include <functional>

namespace Tests{
class Assert{
private:
  unsigned int total = 0;
  unsigned int passed = 0;

public:
  void assertion(const std::string& assertText, bool state){
    total++;
    if(!state)
      printf("%s\n", assertText.c_str());  
    else
      passed++;
  };

  void equal(const std::string& assertText, const std::string& tested, const std::string& correct){
    total++;

    if(tested != correct){
      printf("%s\n", assertText.c_str());
      printf("Tested: %s\n", tested.c_str());
      printf("Correct: %s\n", correct.c_str());
      return;
    }
    else
      passed++;
  };

  void clear() { total = 0; passed = 0; };
  bool results(const std::string& text){
    printf("=== %s ===\n%d/%d passed\n", text.c_str(), passed, total);
    return passed == total;
  };
};
};
