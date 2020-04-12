#include <iostream>

#include "window.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

window::window(guy_manager gm) : _window(NULL),
                                _quit(false),
                                _gm(gm) {
}

window::~window() {
  close();
}

bool window::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << __func__ << "SDL could not initialize! SDL_Error:"
                << SDL_GetError() << std::endl;
      return false;
  } else {
    // Create window
    _window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window,
                                       -1,
                                       SDL_RENDERER_ACCELERATED |
                                       SDL_RENDERER_TARGETTEXTURE);
    if (_window == NULL || _renderer == NULL) {
      std::cerr << __func__ << "Window/rederer could not be created! SDL_Error:"
                <<  SDL_GetError() << std::endl;
      return false;
    } else {
      SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
  }
  // Load guy
  return _gm.load_guy(_renderer);
}

void window::close() {
  SDL_DestroyRenderer(_renderer);
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
            // Left graphics should be loaded
            _gm.set_left_graphic(true);
            break;
          case SDLK_RIGHT:
            _gm.set_x_velo(guy_movement::GOING_RIGHT*5);
            // Right graphics should be loaded
            _gm.set_left_graphic(false);
            break;
          case SDLK_UP:
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
   _gm.load_guy(_renderer);
}

void window::clear_screen() {
  // Clear screen
  SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(_renderer);
}

void window::render() {
	// Render to screen
  //SDL_Rect  tmp = _gm.create_graphic(_gm.get_x_cord(), _gm.get_x_cord());
  SDL_Rect renderQuad = {_gm.get_x_cord(), _gm.get_y_cord(), _gm.get_width(), _gm.get_height()};
	SDL_RenderCopyEx(_renderer, _gm.get_guy_texture(), NULL,
                   &renderQuad,
                   0.0, NULL, SDL_FLIP_NONE);
  SDL_RenderPresent(_renderer);
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
