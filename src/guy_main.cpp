#include "guy_manager.hpp"
#include "guy.hpp"
#include <iostream>


int main() {
  guy_manager gm(1,2);
  std::cerr << "get " << gm.get_x_cord() << std::endl;
}
