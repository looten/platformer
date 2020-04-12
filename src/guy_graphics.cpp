#include <iostream>
#include "guy_graphics.hpp"

guy_graphics::guy_graphics() : _load_left_graphics(false) {
}

guy_graphics::~guy_graphics() {
  SDL_DestroyTexture(_guy_texture_left);
  SDL_DestroyTexture(_guy_texture_right);
}

bool guy_graphics::load_guy(SDL_Renderer* renderer) {
  bool ret = load(renderer, _guy_texture_left, "graphics/guy_left.bmp");
  ret = ret && load(renderer, _guy_texture_right, "graphics/guy_right.bmp");
  return ret;
}

bool guy_graphics::load(SDL_Renderer* renderer, SDL_Texture*& guy_texture, const std::string &path) {
  SDL_Texture* new_texture;
  SDL_Surface* guy_graphic = SDL_LoadBMP(path.c_str());
  if (guy_graphic == NULL) {
    std::cerr << "Unable to load image SDL_image Error \n";
    return false;
  } else {
    new_texture = SDL_CreateTextureFromSurface(renderer, guy_graphic);
    if(new_texture == NULL) {
      std::cerr << "Unable to create texture from %s! SDL Error: \n";
      return false;
    } else {
      //Get image dimensions
      _width = guy_graphic -> w;
      _height = guy_graphic -> h;
    }
    SDL_FreeSurface(guy_graphic);
  }

  // Store texture
  guy_texture = new_texture;
  return true;
}

SDL_Rect guy_graphics::create_graphic(const int &x, const int &y) {
  // Set rendering space and render to screen
	SDL_Rect guy_rect = {x, y, get_width(), get_height()};
  return guy_rect;
}

SDL_Texture* guy_graphics::get_guy_texture() {
  if (_load_left_graphics)
    return _guy_texture_left;
  else
   return _guy_texture_right;
 }
