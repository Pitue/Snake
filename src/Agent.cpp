//
// Created by Marc on 04.03.2022.
//
#include "pch.h"
#include "Agent.h"
#include "Snake.h"
#include "Game.h"

Agent::Agent(Snake *snake, Game *game)
  : snake_{snake}
  , game_{game} {


}

Direction Agent::Calc(const State &s) {


  unsigned int n_dir = game_->get_random_number() % 4;
  return static_cast<Direction>(n_dir);
}
void Agent::Reward(int value) {

}