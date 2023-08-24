#include "snake.h"
#include <cmath>
#include <iostream>


void Snake::Update() {
  switch (direction) {
    case Direction::kNone:
      speed = 0;
      break;

    case Direction::kUp:
      speed = .1f;
      head_y -= speed;
      break;

    case Direction::kDown:
      speed = .1f;
      head_y += speed;
      break;

    case Direction::kLeft:
      speed = .1f;
      head_x -= speed;
      break;

    case Direction::kRight:
      speed = .1f;
      head_x += speed;
      break;

  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  return false;
}