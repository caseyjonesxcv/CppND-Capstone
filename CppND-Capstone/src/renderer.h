#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"





class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, std::vector<SDL_Point> const &food);
  //void Render(Snake const snake, Alien const alien);
  void UpdateWindowTitle(/*int score,*/ int fps);

 private:
  SDL_Window *sdl_window = NULL;
  SDL_Renderer *sdl_renderer = NULL;
  const char *background_path = "../images/space.bmp";
  SDL_Surface *sdl_background = SDL_LoadBMP(background_path);
  SDL_Texture *sdl_backgroundtexture = NULL;
  SDL_Surface *sdl_surface = NULL;
  const char *ship_path = "../images/spaceship.bmp";
  const char *alien_path = "../images/alien.bmp";
  SDL_Surface *sdl_ship = SDL_LoadBMP(ship_path);
  SDL_Surface *sdl_alien = SDL_LoadBMP(alien_path);
  SDL_Texture *sdl_alientexture = NULL;
  SDL_Texture *sdl_shiptexture = NULL;
  const char *explosion_path = "../images/explosion.bmp";
  SDL_Surface *sdl_explosion = SDL_LoadBMP(explosion_path);
  SDL_Texture *sdl_explosiontexture = NULL;
  const char *gameover_path = "../images/gameover.bmp";
  SDL_Surface *sdl_gameover = SDL_LoadBMP(gameover_path);
  SDL_Texture *sdl_gameovertexture = NULL;
  
  

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif