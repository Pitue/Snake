//
// Created by marc on 28.01.22.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "Texture.h"
#include "misc.h"

class Game;

class Snake {
  struct Element {
    int x, y;

    Element(int x, int y)
        : x{x}, y{y} {}

    inline bool operator==(const Element &other) const {
      return (x == other.x && y == other.y);
    }
  };

  Game *game_;
  Texture body_, head_;
  Direction direction_;

  Uint64 delay_;
  bool rotate_;
  std::vector<Element> elements_;

  Mix_Chunk *dying_,
            *eating_;

  void IncreaseSize();

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
        head_.set_rotation(180.0);
        break;
      case Direction::RIGHT:
        head_.set_rotation(270.0);
        break;
      case Direction::LEFT:
        head_.set_rotation(90.0);
        break;
      case Direction::DOWN:
        head_.set_rotation(0.0);
        break;
    }
    rotate_ = true;
  }

  inline bool CheckPosition(SDL_Point pos) {
    return std::find(elements_.begin(), elements_.end(), Element(pos.x, pos.y)) == elements_.end();
  }

  void Tick(size_t time);
  void Render();

  [[nodiscard]] Uint32 get_length() const {
    return elements_.size();
  }
};


#endif//SNAKE_SNAKE_H
