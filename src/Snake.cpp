//
// Created by marc on 28.01.22.
//

#include "pch.h"
#include "Snake.h"
#include "Game.h"

void Snake::IncreaseSize() {
  elements_.emplace_back(elements_.back());
}

Snake::Snake(Game *game)
  : body_(game->renderer_, SNAKE_FILE)
  , head_(game->renderer_, SNAKE_HEAD_FILE)
  , game_{game}
  , direction_{Direction::RIGHT}
  , delay_{0}
  , rotate_{false}
  , eating_{nullptr}
  , dying_{nullptr}{
  eating_ = Mix_LoadWAV(SFX_EATING_FILE);
  if (!eating_)
    OnError(fmt::format("Couldn't load file \"{}\": {}", SFX_EATING_FILE, Mix_GetError()).c_str());

  dying_ = Mix_LoadWAV(SFX_DYING_FILE);
  if (!dying_)
    OnError(fmt::format("Couldn't load file \"{}\": {}", SFX_DYING_FILE, Mix_GetError()).c_str());

  body_.set_center(0, 0);
  body_.set_size(TILE_SIZE, TILE_SIZE);

  head_.set_size(TILE_SIZE, TILE_SIZE);
  head_.set_center(TILE_SIZE / 2, TILE_SIZE / 2);
  head_.set_rotation(270.0);

  elements_.emplace_back(5, 5);
  elements_.emplace_back(4, 5);
  elements_.emplace_back(3, 5);
}
Snake::~Snake() {
  Mix_FreeChunk(eating_);
  Mix_FreeChunk(dying_);
}

void Snake::Tick(Uint64 time) {
  if ((delay_ += time) >= SPEED) {
    delay_ -= SPEED;

    Element n_pos{elements_[0]};
    switch (direction_) {
      case Direction::UP:
        n_pos.y -= 1;
        break;
      case Direction::RIGHT:
        n_pos.x += 1;
        break;
      case Direction::LEFT:
        n_pos.x -= 1;
        break;
      case Direction::DOWN:
        n_pos.y += 1;
        break;
    }
    rotate_ = false;

    //Interaction
    if (n_pos.x < 0 || n_pos.x >= FIELD_SIZE_REL ||
        n_pos.y < 0 || n_pos.y >= FIELD_SIZE_REL) {
#ifdef _DEBUG
      std::cout << fmt::format("Crossed border! Pos: {} | {}\n", n_pos.x, n_pos.y);
#endif

      Mix_PlayChannel(-1, dying_, 0);
      game_->EndGame();
      return;
    }

    if (n_pos.x == game_->get_food_pos().x && n_pos.y == game_->get_food_pos().y) {
      Mix_PlayChannel(-1, eating_, 0);
      IncreaseSize();
      game_->RegenFood();
      game_->RenderScore();
    }

    for (size_t i = 1; i < elements_.size(); ++i) {
      if (n_pos == elements_[i]) {
        Mix_PlayChannel(-1, dying_, 0);
        game_->EndGame();
        return;
      }
    }
    //Interaction

    for (Uint32 i = elements_.size(); i > 0; --i) {
      elements_[i] = elements_[i - 1];
    }
    elements_[0] = n_pos;
  }
}
void Snake::Render() {
  head_.RenderAt((int)elements_[0].x * TILE_SIZE, (int)elements_[0].y * TILE_SIZE);
  for (size_t i = 1; i < elements_.size(); ++i) {
    body_.RenderAt((int)elements_[i].x * TILE_SIZE, (int)elements_[i].y * TILE_SIZE);
  }
}