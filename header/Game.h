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
          score_,
          powerup_text_;
  SDL_Point food_pos;
  bool pause_,
          game_over_;

  Uint32 highscore_;
  std::fstream filestream_;

  bool powerup_;

  void Restart();
  void ToggleStop();
public:
  SDL_Renderer *renderer_;

  explicit Game(SDL_Renderer *renderer);
  ~Game();

  [[nodiscard]] inline SDL_Point get_food_pos() {
    return food_pos;
  }
  [[nodiscard]] inline std::mt19937::result_type get_random_number() {
    return prng_();
  }

  void RenderScore();
  void RegenFood();
  void RenderPowerupText(Uint64 time_left);
  void set_powerup(bool val);
  void EndGame();

  void HandleEvent(SDL_Event *evt);
  void Tick(Uint64 ms);
  void Render();
};


#endif//SNAKE_GAME_H
