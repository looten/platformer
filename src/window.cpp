#include <iostream>

#include "window.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

window::window() : _window(NULL),
                  _screen_surface(NULL),
                  _quit(false) {
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
    if (_window == NULL) {
      std::cerr << __func__ << "Window could not be created! SDL_Error:"
                <<  SDL_GetError() << std::endl;
    } else {
      // Get window surface
      _screen_surface = SDL_GetWindowSurface(_window);

      // Fill the surface white
      SDL_FillRect(_screen_surface,
                   NULL,
                   SDL_MapRGB(_screen_surface->format, 0xFF, 0xFF, 0xFF));

      // Update the surface
      SDL_UpdateWindowSurface(_window);
      success = true;
    }
  }
  return success;
}

void window::close() {
  // Destroy window
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
    case SDL_KEYUP:
      std::cerr << __func__ << " key up event" << std::endl;
      break;
    case SDL_KEYDOWN:
      std::cerr << __func__ << " key down event" << std::endl;
      break;
    case SDL_MOUSEBUTTONDOWN:
      std::cerr << __func__ << " mouse down" << std::endl;
      break;
    case SDL_MOUSEBUTTONUP:
      std::cerr << __func__ << " mouse up" << std::endl;
      break;
    /*default:
      std::cerr << __func__ << " unknown event" << std::endl;
      break;*/
  }
}

void window::loop() {
  while (!_quit) {
    while (SDL_PollEvent(&_event) != 0)
      handle_event();
  }
}
