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
    bool load_guy();
    void render();
 private:
   // The window we'll be rendering to
   SDL_Window* _window;
   // SDL_Surface* _guy_graphic;
   SDL_Renderer* _guy_renderer;
   SDL_Texture* _guy_texture;

   // The surface contained by the window
   SDL_Texture* _screen_texture;

   bool _quit;

   // Event handler
   SDL_Event _event;

   void handle_event();
   bool draw_guy();

   int mWidth;
   int mHeight;

   guy_manager _gm;
};

#endif  // SRC_WINDOW_H_
