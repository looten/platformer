#include <map>
#include <iostream>

#include "guy_manager.hpp"
//#include "guy.hpp"

guy_manager::guy_manager(int x, int y) : guy(x,y) {

}

bool guy_manager::init() {
  return false;
}

bool guy_manager::spawn() {
  return false;
}

void guy_manager::update_pos() {
  set_x_cord(get_x_cord() + get_x_velo());
  set_y_cord(get_y_cord() + get_y_velo());
}

void guy_manager::report_pos() {
  std::cerr << "current pos: x: " << get_x_cord() << " y: " <<  get_y_cord()
            << std::endl;
}

void guy_manager::kill() {
}
