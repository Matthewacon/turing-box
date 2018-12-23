#include "board.h"

#pragma once

//Simple text scrolling. Minimum 4x4. Auto scales to closest lower multiple of 4.
class Text final : public BoolBoard {
private:
 char *str;
 
 unsigned int clen;

public:
 enum ScrollMode {
  HORIZONTAL, VERTICAL
 };

 enum Charset {
  ASCII
 };
 
 Text(unsigned int len, unsigned int width, char *str, unsigned int clen, SEED seed, RNG rng) : BoolBoard(len, width, seed, rng), str(str), clen(clen) {}

 ~Text() {}

 void update() {}
};
