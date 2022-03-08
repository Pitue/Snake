//
// Created by Marc on 04.03.2022.
//

#ifndef SNAKE_AGENT_H
#define SNAKE_AGENT_H

#include "misc.h"

class Snake;
class Game;

struct State {

};

class Agent {
  Snake *snake_;
  Game *game_;

public:
  explicit Agent(Snake *snake, Game *game);
  ~Agent() = default;

  Direction Calc(const State &s);
  void Reward(int value);

};


#endif//SNAKE_AGENT_H
