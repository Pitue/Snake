//
// Created by marc on 28.01.22.
//

#include "Snake.h"
#include "Game.h"
#include "pch.h"

void Snake::IncreaseSize() {
  elements_.emplace_back(elements_.back());
}

Snake::Snake(Game *game)
    : body_(game->renderer_, SNAKE_FILE), head_(game->renderer_, SNAKE_HEAD_FILE), game_{game}, direction_{Direction::RIGHT}, delay_{0}, rotate_{false}, eating_{nullptr}, dying_{nullptr}, powerup_{false}, powerup_left_ticks_{0}, powerup_on_{nullptr}, powerup_off_{nullptr} {
  eating_ = LoadSFX(SFX_EATING_FILE);
  dying_ = LoadSFX(SFX_DYING_FILE);
  powerup_on_ = LoadSFX(SFX_POWERUP_ON_FILE);
  powerup_off_ = LoadSFX(SFX_POWERUP_OFF_FILE);

  body_.set_center(0, 0);
  body_.set_size(TILE_SIZE, TILE_SIZE);

  head_.set_size(TILE_SIZE, TILE_SIZE);
  head_.set_center(TILE_SIZE / 2, TILE_SIZE / 2);
  head_.set_rotation(90.0);

  elements_.emplace_back(5, 5);
  elements_.emplace_back(4, 5);
  elements_.emplace_back(3, 5);
}
Snake::~Snake() {
  Mix_FreeChunk(eating_);
  Mix_FreeChunk(dying_);
}

void Snake::Tick(Uint64 time) {
#ifdef _DEBUG
  std::cout << "Ticks passed: " << time << "\n";
#endif

  if ((delay_ += time) >= SPEED) {
    delay_ -= SPEED;

    if (powerup_) {
      if (time > powerup_left_ticks_) {
        powerup_ = false;
        powerup_left_ticks_ = 0;
        game_->set_powerup(false);
        Mix_PlayChannel(-1, powerup_off_, 0);
      } else {
        powerup_left_ticks_ -= time;
        game_->RenderPowerupText(powerup_left_ticks_);
      }
    }

    for (Uint32 i = elements_.size() - 1; i > 0; --i) {
      elements_[i] = elements_[i - 1];
    }

    Element &head = elements_[0];
    switch (direction_) {
      case Direction::UP:
        head.y -= 1;
        break;
      case Direction::RIGHT:
        head.x += 1;
        break;
      case Direction::LEFT:
        head.x -= 1;
        break;
      case Direction::DOWN:
        head.y += 1;
        break;
    }
    rotate_ = false;

    //Interaction
    if (head.x < 0 || head.x >= FIELD_SIZE_REL ||
        head.y < 0 || head.y >= FIELD_SIZE_REL) {
#ifdef _DEBUG
      std::cout << fmt::format("Crossed border! Pos: {} | {}\n", head.x, head.y);
#endif
      if (!powerup_) {
        Mix_PlayChannel(-1, dying_, 0);
        game_->EndGame();
        return;
      } else {
        if (head.x < 0)
          head.x = FIELD_SIZE_REL - 1;
        else if (head.x >= FIELD_SIZE_REL)
          head.x = 0;

        if (head.y < 0)
          head.y = FIELD_SIZE_REL - 1;
        else if (head.y >= FIELD_SIZE_REL)
          head.y = 0;
      }
    }


    if (head.x == game_->get_food_pos().x && head.y == game_->get_food_pos().y) {
      IncreaseSize();
      game_->RegenFood();
      game_->RenderScore();

      if (game_->get_random_number() % 100 < 10) {
        powerup_ = true;
        powerup_left_ticks_ = POWERUP_TIME;
        game_->set_powerup(true);
        Mix_PlayChannel(-1, powerup_on_, 0);
      } else {
        Mix_PlayChannel(-1, eating_, 0);
      }
    }

    bool found = false;
    for (size_t i = 1; i < elements_.size(); ++i) {
      if (elements_[i] == head) {
        found = true;
        break;
      }
    }
    if (found) {
      Mix_PlayChannel(-1, dying_, 0);
      game_->EndGame();
      return;
    }
    //~Interaction
  }
}
void Snake::Render() {
  for (size_t i = 1; i < elements_.size(); ++i) {
    body_.RenderAt((int) elements_[i].x * TILE_SIZE, (int) elements_[i].y * TILE_SIZE);
  }
  head_.RenderAt((int) elements_[0].x * TILE_SIZE, (int) elements_[0].y * TILE_SIZE);
}