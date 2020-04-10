#include <iostream>

#include "guy_manager.hpp"
#include "guy.hpp"

guy::guy(int x_cord, int y_cord) : _x_cord(x_cord),
                                   _y_cord(y_cord),
                                   _x_velo(guy_movement::STILL),
                                   _y_velo(guy_movement::STILL) {
  std::cout << __func__ << " created guy at (x,y): (" << get_x_cord() << "," << get_y_cord()
            << ")"<< std::endl;
}
