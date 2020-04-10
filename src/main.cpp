#include <iostream>
#include "window.hpp"
#include "guy_manager.hpp"

int main(int argc, char* args[]) {
  guy_manager gm(0, 0);
  window w(gm);
  if (w.init()) {
    w.loop();
  } else {
    std::cerr << __func__ << " failed to init window" << std::endl;
  }
  w.close();
  return 0;
}
