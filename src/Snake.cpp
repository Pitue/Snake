//
// Created by marc on 28.01.22.
//

#include "pch.h"
#include "Snake.h"
#include "Game.h"

void Snake::IncreaseSize() {
  elements_.emplace_back(elements_[length_]);
  ++length_;
}

Snake::Snake(Game *game)
  : body_(game->renderer_, "./resource/snake.png")
  , head_(game->renderer_, "./resource/snake_head.png")
  , game_{game}
  , direction_{Direction::RIGHT}
  , length_{0}
  , delay_{0}
  , rotate_{false}{
  body_.set_center(0, 0);
  body_.set_size(TILE_SIZE, TILE_SIZE);

  head_.set_size(TILE_SIZE, TILE_SIZE);
  head_.set_center(TILE_SIZE / 2, TILE_SIZE / 2);
  head_.set_rotation(270.0);

  elements_.emplace_back(5, 5);

  IncreaseSize();
  IncreaseSize();
}

void Snake::Tick(Uint64 time) {
  if ((delay_ += time) >= SPEED) {
    delay_ -= SPEED;

    for (Uint32 i = length_; i > 0; --i) {
      elements_[i] = elements_[i - 1];
    }
    switch (direction_) {
      case Direction::UP:
        elements_[0].y -= 1;
        break;
      case Direction::RIGHT:
        elements_[0].x += 1;
        break;
      case Direction::LEFT:
        elements_[0].x -= 1;
        break;
      case Direction::DOWN:
        elements_[0].y += 1;
        break;
    }
    rotate_ = false;

    //Interaction
    if (elements_[0].x < 0 || elements_[0].x >= FIELD_SIZE_REL ||
        elements_[0].y < 0 || elements_[0].y >= FIELD_SIZE_REL) {
#ifdef _DEBUG
      std::cout << fmt::format("Crossed border! Pos: {} | {}\n", elements_[0].x, elements_[0].y);
#endif

      Game::EndGame();
    }

    if (elements_[0].x == game_->get_food_pos().x && elements_[0].y == game_->get_food_pos().y) {
      IncreaseSize();
      game_->RegenFood();
      game_->RenderScore();
    }

    for (size_t i = 1; i < elements_.size(); ++i) {
      if (elements_[0] == elements_[i]
          )
        Game::EndGame();
    }
    //Interaction
  }
}
void Snake::Render() {
  head_.RenderAt((int)elements_[0].x * TILE_SIZE, (int)elements_[0].y * TILE_SIZE);
  for (size_t i = 1; i < elements_.size(); ++i) {
    body_.RenderAt((int)elements_[i].x * TILE_SIZE, (int)elements_[i].y * TILE_SIZE);
  }
}