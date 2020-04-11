#include <iostream>

#include "window.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

window::window(guy_manager gm) : _window(NULL),
                                _screen_texture(NULL),
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
      SDL_SetRenderDrawColor( _guy_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

      success = true;
    }
  }
  return success;
}

void window::close() {
  SDL_DestroyTexture(_screen_texture);
  SDL_DestroyTexture(_guy_texture);
  SDL_DestroyRenderer(_guy_renderer);
  // Deallocate guy
  // SDL_FreeSurface(_guy_graphic);
  //_guy_graphic = NULL;
  // Destroy window
  SDL_DestroyWindow(_window);

  // Quit SDL subsystems
  SDL_Quit();
}

void window::handle_event() {
  // guy my_guy = _gm.get_guy();
  switch (_event.type) {
    case SDL_QUIT:
      std::cerr << __func__ << " exit program" << std::endl;
      _quit = true;
      break;
    case SDL_KEYDOWN:
        switch (_event.key.keysym.sym) {
          case SDLK_LEFT:
            _gm.set_x_velo(guy_movement::GOING_LEFT);
            break;
          case SDLK_RIGHT:
            _gm.set_x_velo(guy_movement::GOING_RIGHT);
            break;
          case SDLK_UP:
            _gm.set_y_velo(guy_movement::GOING_UP);
            break;
          case SDLK_DOWN:
            _gm.set_y_velo(guy_movement::GOING_DOWN);
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
          if (_gm.get_x_velo() > guy_movement::STILL)
            _gm.set_x_velo(guy_movement::STILL);
          break;
        case SDLK_UP:
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
      break;
  }
  // std::cout << "x_velo: " << _gm.get_x_velo() << " y_velo: " << _gm.get_y_velo()<< "\n";
  /* Update player position */
  _gm.update_pos();
}

bool window::load_guy() {
  SDL_Texture* newTexture;
  SDL_Surface* _guy_graphic = SDL_LoadBMP("graphics/guy_right.bmp");
  if (_guy_graphic == NULL) {
    std::cerr << "Unable to load image SDL_image Error \n";
  } else {
    // _screen_texture = SDL_CreateTexture(_guy_renderer, _guy_graphic);
    newTexture = SDL_CreateTextureFromSurface(_guy_renderer, _guy_graphic);
    if(newTexture == NULL) {
      std::cerr << "Unable to create texture from %s! SDL Error: \n";
    } else {
      //Get image dimensions
      mWidth = _guy_graphic -> w;
      mHeight = _guy_graphic -> h;
    }
    SDL_FreeSurface(_guy_graphic);
  }
  _guy_texture = newTexture;
}


/*void::window::draw_guy() {
  //Loading success flag
bool success = true;
  // Load splash image
  if (_gm.set_x_velo() == guy_movement::GOING_LEFT) {

  } else {

  }

  r.x = get_x_cord
  r.y =rand()%500;

  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);
  SDL_RenderDrawRect(renderer,&r);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
  SDL_RenderFillRect(renderer, &r);
  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);


  return success;
}*/

void window::render() {
  //Set rendering space and render to screen
	SDL_Rect renderQuad = { _gm.get_x_cord(), _gm.get_y_cord(), mWidth, mHeight };

	//Set clip rendering dimensions
	/*if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}*/

	//Render to screen
	SDL_RenderCopyEx(_guy_renderer, _guy_texture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE );
}

void window::loop() {
  while (!_quit) {
    while (SDL_PollEvent(&_event) != 0) {
      handle_event();
    }

    //_gm.report_pos();

    //Clear screen
    SDL_SetRenderDrawColor(_guy_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_guy_renderer);

    render();

    SDL_RenderPresent(_guy_renderer);
    // SDL_Delay(1000);
  }
}
