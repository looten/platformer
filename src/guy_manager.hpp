#ifndef SRC_GUY_MANAGER_H_
#define SRC_GUY_MANAGER_H_

#include <map>

#include "guy.hpp"
#include "guy_graphics.hpp"

// #include "guy.hpp"

namespace guy_movement {
  const int STILL = 0;
  const int GOING_RIGHT = 1;
  const int GOING_LEFT = -1;
  const int GOING_UP = -1;
  const int GOING_DOWN = 1;
};

class guy_manager : public guy, public guy_graphics {
 public:
    guy_manager(int x, int y);
    // virtual ~guy_manager() {}
    bool init();
    bool spawn();
    void update_pos();
    void kill();
    void handle_movement();
    void report_pos();
    //guy get_guy() { return _guy; }
 private:
   // static std::map<int, guy> guys;
   // guy _guy;
};

#endif  // SRC_GUY_MANAGER_H_
