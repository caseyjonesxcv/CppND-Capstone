#include "game.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
   PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 title_timestamp2 = SDL_GetTicks();
  Uint32 title_timestamp3 = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
 

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
      
      }

    if (frame_end - title_timestamp2 >= 900) {
      PlaceFood();
      title_timestamp2 = frame_end;
    }

    if (frame_end - title_timestamp3 >= 500){
      for(int i = 0; i < food.size(); i++){
        food[i].y += 1;
        }
      title_timestamp3 = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


void Game::PlaceFood() {

  int x, y;
    x = random_w(engine);
    y = 0;
    SDL_Point position = {x,y};
    food.push_back(position);    
  }


void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  //Check if there's food over here
  for(int i = 0; i < food.size(); i++){
  if (food[i].x == new_x && food[i].y == new_y) {
    snake.alive = false;
    }
   if (food[i].y >= 30) {
    food.erase(food.begin());
    score++;
    }
  } 
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }