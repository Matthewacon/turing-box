#pragma once

template<typename T>
struct Point {
public:
 T x, y;

 Point(T x, T y) : x(x), y(y) {}
};

template<typename T>
class Board {
public:
 unsigned int
  len,
  width,
  total_size;
 
 T *board;

 explicit Board(unsigned int len, unsigned int width) : len(len), width(width) {
  total_size = len * width;
  board = new T[total_size];
 }

// virtual ~Board() = 0;

 ~Board() {
  delete[] board;
 }
 
 T get(unsigned int x, unsigned int y) {
  return get(calculate_index(x, y));
 }

 T get(unsigned int index) {
  return board[index];
 }

 void set(unsigned int x, unsigned int y, T flag) {
  set(calculate_index(x, y), flag);
 }

 void set(unsigned int index, T flag) {
  board[index] = flag;
 }

 unsigned int calculate_index(unsigned int x, unsigned int y) {
  return (x * len) + y;
 }

 Point<unsigned int> calculate_index(unsigned int index) {
  return {
   //note: intentional flooring
   .x = index / len,
   .y = index - ((index / len) * len)
  };
 }

 unsigned int wrap_around(int x, int bound) {
  if (x < 0) {
   while ((x += bound) < 0);
  } else if (x > bound - 1) {
   while ((x -= bound) >= bound - 1);
  }
  /*
  bound = (x < 0 ? -bound : bound);
  while ((x += bound) < 0);
  */
  return static_cast<unsigned int>(x); 
 }

 //TODO assignment operator for array access on games
 T operator[] (const unsigned int index) {
  return board[index];
 }

/*
 //Allows for multidimensional access to board
 //ex) my_game[0][2] -> bool;
 bool * operator[] (const unsigned int index) {
  if (index >= x) {
   index = wrap_around(index, len);
  }
  //TODO truncate length of returned pointer to (width)
  return board + index;
 }
*/

 virtual void update() = 0;
};

typedef int (*RNG)(int min, int max);
typedef void (*SEED)();

class BoolBoard : public Board<bool> {
private:
 SEED seed;

 RNG rng;

public:
 BoolBoard(unsigned int len, unsigned int width, SEED seed, RNG rng) : Board(len, width), seed(seed), rng(rng) {}

// virtual ~BoolBoard() = 0;

 virtual void update() = 0; 

 void clear_board() {
  for (unsigned int i = 0; i < total_size; i++) {
   set(i, false);
  }
 }

 void seed_random() {
  seed();
 }

 int random_num(int min, int max) {
  seed_random();
  return rng(min, max);
 }

 void generate_random_board() {
  seed_random();
  for (unsigned int i = 0; i < total_size; i++) {
   set(i, rng(0, 1023) > 512);
  }
 }
};
