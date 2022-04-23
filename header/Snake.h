//
// Created by marc on 28.01.22.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "Texture.h"
#include "misc.h"

class Game;

class Snake {
  Game *game_;
  Texture body_, head_;
  Direction direction_;

  Uint64 delay_;
  bool rotate_;
  std::vector<Position> snake_;

  Mix_Chunk *sfx_dying_,
            *sfx_eating_,
            *sfx_powerup_on_,
            *sfx_powerup_off_;

  bool powerup_;
  int_fast64_t powerup_ticks_left_;

  void Grow();

public:
  explicit Snake(Game *game);
  ~Snake();

  inline void set_direction(Direction dir) {
    if (
        rotate_ ||
        dir == direction_ ||
        (IsHorizontal(dir) && IsHorizontal(direction_)) ||
        (IsVertical(dir) && IsVertical(direction_)))
      return;

    direction_ = dir;
    switch (dir) {
      case Direction::UP:
        head_.set_rotation(0.0);
        break;
      case Direction::RIGHT:
        head_.set_rotation(90.0);
        break;
      case Direction::LEFT:
        head_.set_rotation(270.0);
        break;
      case Direction::DOWN:
        head_.set_rotation(180.0);
        break;
    }
    rotate_ = true;
  }

  inline bool CheckPosition(Position pos) {
    return std::find(snake_.begin(), snake_.end(), Position(pos.x, pos.y)) == snake_.end();
  }

  void Tick(size_t time);
  void Render();

  [[nodiscard]] Uint32 get_length() const {
    return snake_.size();
  }
};


#endif//SNAKE_SNAKE_H
