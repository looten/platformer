#ifndef SRC_GUY_GRAPHICS_H_
#define SRC_GUY_GRAPHICS_H_

#include <SDL.h>

class guy_graphics {
 public:
   guy_graphics();
   ~guy_graphics();
   bool load_guy(SDL_Renderer* renderer);
   void set_left_graphic(const bool &load_left_graphics) {_load_left_graphics = load_left_graphics;}
   bool is_left_graphic() {return _load_left_graphics;}
   SDL_Rect create_graphic(const int &x, const int &y);


   SDL_Texture* get_guy_texture();
   // Width and height
   int get_width() { return _width; }
   int get_height() { return _height; }
   void set_width(const int &w) { _width = w; }
   void set_height(const int &h) { _height = h; }
 private:
   bool load(SDL_Renderer* renderer, SDL_Texture*& texture, const std::string &path);
   SDL_Texture* _guy_texture_left;
   SDL_Texture* _guy_texture_right;
   bool _load_left_graphics;
   int _width;
   int _height;
};

#endif  // SRC_GUY_GRAPHICS_H_
