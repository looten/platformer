#include "guy.hpp"
#include <iostream>

guy::guy(int x, int y) : _x_cord(x), _y_cord(y) {
  std::cout << __func__ << " created guy at (x,y): (" << get_x_cord() << "," << get_y_cord()
            << ")"<< std::endl;
}

/*int main() {
  guy main_guy;
  std::cout << " platformer_main: " << main_guy.add_5(0) << std::endl;
  return 0;
}*/
