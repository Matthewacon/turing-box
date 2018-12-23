#include "board.h"

#pragma once

//A modified version of Conway's Game of Life ruleset that makes recurrent changes to the board
class AntiConway final : public BoolBoard {
public:
 using BoolBoard::BoolBoard;
 
 void update() {
  for (unsigned int i = 0; i < total_size; i++) {
   Point point = calculate_index(i);
   unsigned int neighbours = 0;
   for (int j = -1; j < 2; j++) {
    for (int k = -1; k < 2; k++) {
     if (!(j == 0 && k == 0)) {
      unsigned int index = wrap_around(point.x + j, len) * len + wrap_around(point.y + k, width);
      if ((*this)[index]) {
       neighbours += 1;
      }
     }
    }
    set(i, neighbours == 2 || neighbours == 3);
   }
  }
 }
};
