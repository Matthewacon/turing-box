#include "board.h"

#pragma once

//Ulam Warburton's Automaton 
class Ulam final : public BoolBoard {
public:
// using Game<bool>::Game;
 Ulam(unsigned int len, unsigned int width, SEED seed, RNG rng) : BoolBoard(len, width, seed, rng) {
  set(len / 2, width / 2, true);
 }

 void update() {
  bool *copy = new bool[total_size];
  memcpy(copy, board, sizeof(bool) * total_size);
  for (unsigned int i = 0; i < total_size; i++) {
   if ((*this)[i]) {
    continue;
   }
   unsigned int neighbours = 0;
   Point p = calculate_index(i);
   for (int j = -1; j < 2; j++) {
    if (j == 0) {
     continue;
    }
    unsigned int 
     hor_index = wrap_around(p.x + j, len) * len + p.y,
     vert_index = p.x * len + wrap_around(p.y + j, width);
    if ((*this)[hor_index]) {
     neighbours += 1;
    }
    if ((*this)[vert_index]) {
     neighbours += 1;
    }
   }
   if (neighbours == 1) {
    copy[i] = true;
   }
  }
  delete[] board;
  board = copy;
 }
};
