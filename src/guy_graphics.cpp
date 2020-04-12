#include <iostream>
#include "guy_graphics.hpp"

guy_graphics::guy_graphics() : _load_left_graphics(false) {
}

guy_graphics::~guy_graphics() {
  SDL_DestroyTexture(_guy_texture);
}

bool guy_graphics::load_guy(SDL_Renderer* renderer) {
  SDL_Texture* new_texture;
  SDL_Surface* _guy_graphic;
  if (is_left_graphic()) {
    _guy_graphic = SDL_LoadBMP("graphics/guy_left.bmp");
  } else {
    _guy_graphic = SDL_LoadBMP("graphics/guy_right.bmp");
  }
  if (_guy_graphic == NULL) {
    std::cerr << "Unable to load image SDL_image Error \n";
    return false;
  } else {
    new_texture = SDL_CreateTextureFromSurface(renderer, _guy_graphic);
    if(new_texture == NULL) {
      std::cerr << "Unable to create texture from %s! SDL Error: \n";
      return false;
    } else {
      //Get image dimensions
      _width = _guy_graphic -> w;
      _height = _guy_graphic -> h;
    }
    SDL_FreeSurface(_guy_graphic);
  }

  // Store new guy texture
  _guy_texture = new_texture;
  return true;
}

SDL_Rect guy_graphics::create_graphic(const int &x, const int &y) {
  // Set rendering space and render to screen
	SDL_Rect guy_rect = {x, y, get_width(), get_height()};
  return guy_rect;
}
