#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

// Using SDL and standard IO
#include <SDL.h>

#include "guy_manager.hpp"

class window {
 public:
    window(guy_manager gm);
    ~window();
    bool init();
    void close();
    void loop();
 private:
   // The window we'll be rendering to
   SDL_Window* _window;

   // The surface contained by the window
   SDL_Surface* _screen_surface;

   bool _quit;

   // Event handler
   SDL_Event _event;

   void handle_event();

   guy_manager _gm;
};

#endif  // SRC_WINDOW_H_
