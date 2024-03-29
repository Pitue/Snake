//
// Created by marc on 28.01.22.
//

#include "Snake.h"
#include "Game.h"
#include "pch.h"

void Snake::Grow() {
  snake_.emplace_back(snake_.back());
}

Snake::Snake(Game *game)
    : body_(game->renderer_, SNAKE_FILE)
    , head_(game->renderer_, SNAKE_HEAD_FILE)
    , game_{game}, direction_{Direction::RIGHT}
    , delay_{0}, rotate_{false}
    , sfx_eating_{nullptr}
    , sfx_dying_{nullptr}
    , powerup_{false}
    , powerup_ticks_left_{0}
	  , powerup_cooldown_{0}
    , sfx_powerup_on_{nullptr}
    , sfx_powerup_off_{nullptr} {
  sfx_eating_ = LoadSFX(SFX_EATING_FILE);
  sfx_dying_ = LoadSFX(SFX_DYING_FILE);
  sfx_powerup_on_ = LoadSFX(SFX_POWERUP_ON_FILE);
  sfx_powerup_off_ = LoadSFX(SFX_POWERUP_OFF_FILE);

  body_.set_center(0, 0);
  body_.set_size(TILE_SIZE, TILE_SIZE);

  head_.set_size(TILE_SIZE, TILE_SIZE);
  head_.set_center(TILE_SIZE / 2, TILE_SIZE / 2);
  head_.set_rotation(90.0);

  snake_.emplace_back(3, 5);
  Grow();
  Grow();
}
Snake::~Snake() {
  Mix_FreeChunk(sfx_eating_);
  Mix_FreeChunk(sfx_dying_);
}

void Snake::Tick(Uint64 time) {
  if (powerup_) {
    powerup_ticks_left_ -= time;

    if (powerup_ticks_left_ <= 0) {
      powerup_ = false;
      game_->set_powerup(false);
      Mix_PlayChannel(-1, sfx_powerup_off_, 0);
    } else {
      game_->RenderPowerupText(powerup_ticks_left_);
    }
  }

  if ((delay_ += time) >= SPEED) {
    delay_ -= SPEED;

    for (Uint32 i = snake_.size() - 1; i > 0; --i) {
      snake_[i] = snake_[i - 1];
    }

    Position &head = snake_[0];
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
        Mix_PlayChannel(-1, sfx_dying_, 0);
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
    } else if (std::find(snake_.begin() + 1, snake_.end(), snake_[0]) != snake_.end()) {
      Mix_PlayChannel(-1, sfx_dying_, 0);
      game_->EndGame();
      return;
    } else if (head == game_->get_food_pos()) {
      Grow();
      game_->RegenFood();
      game_->RenderScore();

      if (game_->get_random_number() % 100 < 150 && !powerup_ && powerup_cooldown_ == 0) {
        powerup_ = true;
        powerup_cooldown_ = 5;
        powerup_ticks_left_ = POWERUP_TIME;
        game_->set_powerup(true);
        Mix_PlayChannel(-1, sfx_powerup_on_, 0);
      } else {
        Mix_PlayChannel(-1, sfx_eating_, 0);
        if (powerup_cooldown_ > 0 && !powerup_)
          --powerup_cooldown_;
      } 
    }



    //~Interaction
  }
}
void Snake::Render() {
  for (size_t i = 1; i < snake_.size(); ++i) {
    body_.RenderAt((int) snake_[i].x * TILE_SIZE + BORDER_SIZE_X, (int) snake_[i].y * TILE_SIZE + BORDER_SIZE_Y);
  }
  if (!game_->get_gameover())
    head_.RenderAt((int) snake_[0].x * TILE_SIZE + BORDER_SIZE_X, (int) snake_[0].y * TILE_SIZE + BORDER_SIZE_Y);
}