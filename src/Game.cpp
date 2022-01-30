//
// Created by marc on 29.01.22.
//

#include "pch.h"
#include "Game.h"

Game::Game(SDL_Renderer *renderer)
  : font_{TTF_OpenFont(FONT_FILE, 24)}
  , snake_{nullptr}
  , field_(renderer, "./resource/field.png")
  , food_(renderer,"./resource/food.png")
  , score_(renderer)
  , renderer_{renderer}
  , font_color_{0, 0, 0, SDL_ALPHA_OPAQUE}
  , food_pos{0, 0}
  , pause_{false} {
  food_.set_center(0, 0);
  food_.set_size(TILE_SIZE, TILE_SIZE);

  if (!font_)
    OnError(fmt::format("Couldn't load font \"{}\"", FONT_FILE));

  prng_.seed(time(nullptr));
  Restart();
}
Game::~Game() {
  TTF_CloseFont(font_);

}

void Game::EndGame() {
  SDL_Event evt{SDL_QUIT};
  SDL_PushEvent(&evt);
}

void Game::HandleEvent(SDL_Event *evt) {
  if (!pause_) {
    switch (evt->key.keysym.sym) {
      case SDLK_w:
        snake_->set_direction(Direction::UP);
        break;
      case SDLK_a:
        snake_->set_direction(Direction::LEFT);
        break;
      case SDLK_s:
        snake_->set_direction(Direction::DOWN);
        break;
      case SDLK_d:
        snake_->set_direction(Direction::RIGHT);
        break;
    }
  }

  switch (evt->key.keysym.sym) {
    case SDLK_r:
      Restart();
      break;

    case SDLK_ESCAPE:
      ToggleStop();
      break;

#ifndef NDEBUG
    case SDLK_t:
      RegenFood();
      break;
#endif

    default:
      break;
  }

}

void Game::Tick(Uint64 ms) {
  if (!pause_)
    snake_->Tick(ms);
}

void Game::Render() {
  field_.Render();

  food_.RenderAt(food_pos.x * TILE_SIZE, food_pos.y * TILE_SIZE);
  snake_->Render();

  score_.Render();
}