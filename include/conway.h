#include "board.h"

#pragma once

//Conway's Game of Life
class Conway final : public BoolBoard {
public:
 using BoolBoard::BoolBoard;
 
 void update() {
  bool *copy = new bool[total_size];
  memcpy(copy, board, sizeof(bool) * total_size);
  for (unsigned int i = 0; i < total_size; i++) {
   Point point = calculate_index(i);
   unsigned int neighbours = 0;
   for (int j = -1; j < 2; j++) {
    for (int k = -1; k < 2; k++) {
     unsigned int index = wrap_around(point.x + j, len) * len + wrap_around(point.y + k, width);
     if ((*this)[index]) {
      neighbours += 1;
     }
    }
   }
   if (copy[i]) {
    neighbours -= 1;
   }
   if (neighbours == 2) {
    copy[i] = copy[i];
   } else if (neighbours == 3) {
    copy[i] = true;
   } else {
    copy[i] = false;
   }
  }
  delete[] board;
  board = copy;
 }
};
