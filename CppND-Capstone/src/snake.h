#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kNone, kUp, kDown, kLeft, kRight, kSpace };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  bool SnakeCell(int x, int y);

  Direction direction = Direction::kNone;

  float speed{.1};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private: 
  int grid_width;
  int grid_height;
};

#endif