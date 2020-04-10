#include "platformer.hpp"
#include <iostream>

guy::guy() {
  std::cout << __func__ << " created guy " << std::endl;
}

int guy::add_5(int num) {return num + 5;}

/*int main() {
  guy main_guy;
  std::cout << " platformer_main: " << main_guy.add_5(0) << std::endl;
  return 0;
}*/
