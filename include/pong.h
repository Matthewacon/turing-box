#include "board.h"

#pragma once

//Simple Pong implementation with rudimentary AI
class Pong final : public BoolBoard {
 enum Paddle {
  LEFT, RIGHT
 };

 unsigned int
  ball_x, 
  ball_y,
  paddle_len,
  paddle_left_y,
  paddle_right_y;
  
 int
  ball_vel_x,
  ball_vel_y;

 //TODO
 bool ai_enabled;

private:
 bool paddle_collision(unsigned int x, unsigned int y) {
  //Left paddle
  if (x == 1 && (y == paddle_left_y || y == paddle_left_y + paddle_len)) {
   return true;
  }
  //Right paddle
  if (x == width - 2 && (y == paddle_right_y || y == paddle_right_y + paddle_len)) {
   return true;
  }
  return false;
 }

 void gen_random_velocity() {
  seed_random();
  //ball_vel_x can can't be 0
  while ((ball_vel_x = random_num(-1, 2)) == 0);
  ball_vel_y = random_num(-1, 2);
 }

 void draw_paddle(unsigned int x, unsigned int y) {
  for (unsigned int i = 0; i < paddle_len; i++) {
   set(x, y + i, true);
  }
 }

public:
 Pong(unsigned int len, unsigned int width, unsigned int paddle_len, bool ai, SEED seed, RNG rng) : BoolBoard(len, width, seed, rng), paddle_len(paddle_len), ai_enabled(ai) {
  ball_x = width / 2;
  ball_y = len / 2;
  paddle_left_y = paddle_right_y = len / 2;
  gen_random_velocity();
 }

 void move_paddle(Paddle p, int y) {
  unsigned int *paddle = p == Paddle::LEFT ? &paddle_left_y : &paddle_right_y;
  if (*paddle + y <= 0) {
   *paddle = 0;
  } else if (*paddle + y + 1 >= len) {
   *paddle = len - 1;
  } else {
   *paddle += y;
  }
 }
 
 void update() {
  //Clear screen
  clear_board();
  //Update paddles
  draw_paddle(0, paddle_left_y);
  draw_paddle(width - 1, paddle_right_y);
  //Update ball
  unsigned int 
   new_ball_x = ball_x + ball_vel_x,
   new_ball_y = ball_y + ball_vel_y;
   //If the ball bounces off of the floor or ceiling
   if (new_ball_y == 0 || new_ball_y == len - 1) {
    ball_vel_y = -ball_vel_y;
   }
   //If the ball bounces off of the paddles
   if (paddle_collision(new_ball_x, new_ball_y)) {
    ball_vel_x = -ball_vel_x;
   }
   //If the ball hits left or right walls
   if (ball_x == 0 || ball_x == width - 1) {
    //TODO Scroll text "GOAL!"
    new_ball_x = width / 2;
    new_ball_y = len / 2;
    gen_random_velocity();
   }
   //Update board
   set(new_ball_x, new_ball_y, true);
   ball_x = new_ball_x;
   ball_y = new_ball_y;
   if (ai_enabled) {
    //TODO calculate trajectory of ball (only move paddle if the ball is headed in the paddle's direction)
   }
 }
};
