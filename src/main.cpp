#include <iostream>
#include "window.hpp"

int main(int argc, char* args[]) {
  window w;
  if (w.init()) {
    w.loop();
  } else {
    std::cerr << __func__ << " failed to init window" << std::endl;
  }
  w.close();
  return 0;
}
