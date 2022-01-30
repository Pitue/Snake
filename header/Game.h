//
// Created by marc on 29.01.22.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Texture.h"
#include "Snake.h"
#include "misc.h"


class Game {
  std::mt19937 prng_;
  SDL_Color font_color_;
  TTF_Font *font_;
  Snake *snake_;

  Texture field_,
          food_,
          score_;
  SDL_Point food_pos;
  bool pause_;

  inline void Restart() {
    snake_ = new Snake(this);
    RegenFood();
    RenderScore();
    pause_ = false;
  }
  void ToggleStop() {
    pause_ = !pause_;

    if (pause_) {
      SDL_Surface *surf = TTF_RenderText_Blended(font_, "Paused", font_color_);
      score_.set_texture(&surf);
    } else {
      RenderScore();
    }
  }
public:
  SDL_Renderer *renderer_;

  explicit Game(SDL_Renderer *renderer);
  ~Game();

  inline void RenderScore() {
    SDL_Surface *surf = TTF_RenderText_Blended(font_, fmt::format("Score: {}", snake_->get_length() + 1).c_str(), font_color_);
    score_.set_texture(&surf);
  }
  inline void RegenFood() {
    SDL_Point pos{0,0};
    do {
      pos.x = static_cast<int>(prng_() % FIELD_SIZE_REL);
      pos.y = static_cast<int>(prng_() % FIELD_SIZE_REL);
    } while (!snake_->CheckPosition(pos));
    food_pos = pos;
  }
  [[nodiscard]] inline SDL_Point get_food_pos() {
    return food_pos;
  }

  static void EndGame();

  void HandleEvent(SDL_Event *evt);
  void Tick(Uint64 ms);
  void Render();
};


#endif//SNAKE_GAME_H
