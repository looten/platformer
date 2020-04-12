#include <iostream>

#include "window.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

window::window(guy_manager gm) : _window(NULL),
                                _quit(false),
                                _gm(gm) {
  std::cout << __func__ << " constructor" << std::endl;
}

window::~window() {
  std::cout << __func__ << " de-constructor" << std::endl;
  close();
}

bool window::init() {
  bool success = false;
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << __func__ << "SDL could not initialize! SDL_Error:"
                << SDL_GetError() << std::endl;
  } else {
    // Create window
    _window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    _guy_renderer = SDL_CreateRenderer(_window,
                                       -1,
                                       SDL_RENDERER_ACCELERATED |
                                       SDL_RENDERER_TARGETTEXTURE);
    if (_window == NULL || _guy_renderer == NULL) {
      std::cerr << __func__ << "Window/rederer could not be created! SDL_Error:"
                <<  SDL_GetError() << std::endl;
    } else {
      SDL_SetRenderDrawColor(_guy_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

      success = true;
    }
  }
  return success && load_guy();
}

void window::close() {
  SDL_DestroyTexture(_guy_texture);
  SDL_DestroyRenderer(_guy_renderer);
  SDL_DestroyWindow(_window);
  // Quit SDL subsystems
  SDL_Quit();
}

void window::handle_event() {
  switch (_event.type) {
    case SDL_QUIT:
      std::cerr << __func__ << " exit program" << std::endl;
      _quit = true;
      break;
    case SDL_KEYDOWN:
        switch (_event.key.keysym.sym) {
          case SDLK_LEFT:
            _gm.set_x_velo(guy_movement::GOING_LEFT*5);
            break;
          case SDLK_RIGHT:
            std::cerr << "RIGHT ARROW DOWN\n";
            _gm.set_x_velo(guy_movement::GOING_RIGHT*5);
            break;
          case SDLK_UP:
            std::cerr << "UP ARROW DOWN\n";
            _gm.set_y_velo(guy_movement::GOING_UP*5);
            break;
          case SDLK_DOWN:
            _gm.set_y_velo(guy_movement::GOING_DOWN*5);
            break;
          default:
            break;
        }
        break;
    case SDL_KEYUP:
      switch (_event.key.keysym.sym) {
        case SDLK_LEFT:
          if (_gm.get_x_velo() < guy_movement::STILL)
            _gm.set_x_velo(guy_movement::STILL);
          break;
        case SDLK_RIGHT:
          std::cerr << "RIGHT ARROW UP\n";
          if (_gm.get_x_velo() > guy_movement::STILL)
            _gm.set_x_velo(guy_movement::STILL);
          break;
        case SDLK_UP:
        std::cerr << "UP ARROW UP\n";
          if (_gm.get_y_velo() < guy_movement::STILL)
            _gm.set_y_velo(guy_movement::STILL);
          break;
        case SDLK_DOWN:
          if (_gm.get_y_velo() > guy_movement::STILL)
            _gm.set_y_velo(guy_movement::STILL);
          break;
        default:
          break;
      }
      std::cout << "x_velo: " << _gm.get_x_velo() << " y_velo: " << _gm.get_y_velo()<< "\n";
      break;
  }
}

bool window::load_guy() {
  SDL_Texture* newTexture;
  SDL_Surface* _guy_graphic = SDL_LoadBMP("graphics/guy_right.bmp");
  if (_guy_graphic == NULL) {
    std::cerr << "Unable to load image SDL_image Error \n";
    return false;
  } else {
    newTexture = SDL_CreateTextureFromSurface(_guy_renderer, _guy_graphic);
    if(newTexture == NULL) {
      std::cerr << "Unable to create texture from %s! SDL Error: \n";
      return false;
    } else {
      //Get image dimensions
      mWidth = _guy_graphic -> w;
      mHeight = _guy_graphic -> h;
    }
    SDL_FreeSurface(_guy_graphic);
  }
  _guy_texture = newTexture;
  return true;
}

void window::clear_screen() {
  // Clear screen
  SDL_SetRenderDrawColor(_guy_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(_guy_renderer);
}
void window::render() {
  // Set rendering space and render to screen
	SDL_Rect renderQuad = {_gm.get_x_cord(), _gm.get_y_cord(), mWidth, mHeight};

	// Render to screen
	SDL_RenderCopyEx(_guy_renderer, _guy_texture, NULL, &renderQuad, 0.0, NULL,
                   SDL_FLIP_NONE);
  SDL_RenderPresent(_guy_renderer);
}

void window::loop() {
  const int update_freq_ms = 1;
  const Uint8 *keystate;
  int ret;
  while (!_quit) {
    ret = SDL_WaitEventTimeout(&_event, update_freq_ms);
    if (ret != 0) {
      handle_event();
    }

    keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_LEFT] ||
        keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_UP]) {
      _gm.update_pos();
      clear_screen();
      render();
    }
  }
}
