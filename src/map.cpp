#include "platformer.hpp"
#include <iostream>

map::map(int height, int width) : _height(height), _width(width) {
  std::cout << __func__ << " created map with height: " << get_height() << " width:"
            << get_width() << std::endl;
}
