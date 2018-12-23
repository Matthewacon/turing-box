#include "board.h"

#pragma once

//Langton's Ant cellular automata
class Langton final : public BoolBoard {
 enum Direction : unsigned int {
  NORTH = 0, 
  EAST = 1, 
  SOUTH = 2, 
  WEST = 3
 };

private:
 int 
  ant_x, 
  ant_y;
 
 Direction direction;

public:
 Langton(unsigned int len, unsigned int width, SEED seed, RNG rng) : BoolBoard(len, width, seed, rng) {
  ant_x = len / 2;
  ant_y = width / 2;
  direction = Direction::NORTH;
 }

 void update() {
  bool cell = get(ant_x, ant_y);
  set(ant_x, ant_y, !cell);
  ant_x = wrap_around(ant_x, len);
  ant_y = wrap_around(ant_y, width);
  direction = (Direction)wrap_around(direction + (cell ? 1 : -1), 4);
  switch (direction) {
   case Direction::NORTH: {
    ant_x += 1;
    break;
   }
   case Direction::EAST: {
    ant_y += 1;
    break;
   }
   case Direction::SOUTH: {
    ant_x -= 1;
    break;
   }
   case Direction::WEST: {
    ant_y -= 1;
    break;
   }
  }
 }
};
