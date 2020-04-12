#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

// Using SDL and standard IO
#include <SDL.h>
// #include <SDL_image.h>

#include "guy_manager.hpp"

class window {
 public:
    window(guy_manager gm);
    ~window();
    bool init();
    void close();
    void loop();

 private:
   bool _quit;
   int mWidth;
   int mHeight;
   SDL_Window* _window;
   SDL_Renderer* _guy_renderer;
   SDL_Texture* _guy_texture;
   // Event handler
   SDL_Event _event;

   void handle_event();
   bool load_guy();
   void render();
   void clear_screen();

   guy_manager _gm;
};

#endif  // SRC_WINDOW_H_
