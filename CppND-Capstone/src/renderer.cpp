#include "renderer.h"
#include "game.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>



Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  } else {
    sdl_surface = SDL_GetWindowSurface(sdl_window);
  }
  
 // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_background) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  } else {
    sdl_backgroundtexture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_background);
    SDL_FreeSurface(sdl_background);
  }
    if (nullptr == sdl_alien) {
    std::cerr << "Alien could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  } else {
    sdl_alientexture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_alien);
    SDL_FreeSurface(sdl_alien);
  }
    if (nullptr == sdl_ship) {
    std::cerr << "Ship could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  } else {
    sdl_shiptexture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_ship);
    SDL_FreeSurface(sdl_ship);
  }
    if (nullptr == sdl_explosion) {
    std::cerr << "Explosion could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  } else {
    sdl_explosiontexture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_explosion);
    SDL_FreeSurface(sdl_explosion);
  }
    if (nullptr == sdl_gameover) {
    std::cerr << "Game Over could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  } else {
    sdl_gameovertexture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_gameover);
    SDL_FreeSurface(sdl_gameover);
  }

}

Renderer::~Renderer() {
  
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}


void Renderer::Render(Snake const snake, std::vector<SDL_Point> const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  SDL_Rect ship_rect;
  ship_rect.x = static_cast<int>(snake.head_x) * block.w;
  ship_rect.y = static_cast<int>(snake.head_y) * block.h;
  ship_rect.w = 50;
  ship_rect.h = 50;

  SDL_Rect gameover_rect;
  gameover_rect.x = 160;
  gameover_rect.y = 180;
  gameover_rect.w = 300;
  gameover_rect.h = 300;

  SDL_Rect bullet_rect;
  bullet_rect.x = snake.head_x;
  bullet_rect.y = snake.head_y;

   SDL_RenderClear(sdl_renderer);
   SDL_RenderCopy(sdl_renderer, sdl_backgroundtexture, NULL, NULL);
   for(int i = 0; i < food.size(); i++) {
  
    SDL_Rect alien_rect;
    alien_rect.x = food[i].x * block.w;
    alien_rect.y = food[i].y * block.h;
    alien_rect.w = 50;
    alien_rect.h = 50;
    SDL_RenderCopy(sdl_renderer, sdl_alientexture, NULL, &alien_rect);
   }


    if (snake.alive) {
    SDL_RenderCopy(sdl_renderer, sdl_shiptexture, NULL, &ship_rect);
  } else {
    SDL_RenderCopy(sdl_renderer, sdl_explosiontexture, NULL, &ship_rect);
    SDL_DestroyTexture(sdl_alientexture);
    SDL_RenderCopy(sdl_renderer, sdl_gameovertexture, NULL, &gameover_rect);
  }

   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snake.body) {
    bullet_rect.x = ship_rect.x;
    bullet_rect.y = ship_rect.y;
    bullet_rect.h = 3;
    bullet_rect.w = 3;
    SDL_RenderFillRect(sdl_renderer, &block);
    }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Aliens Avoided: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}