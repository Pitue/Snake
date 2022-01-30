//
// Created by marc on 29.01.22.
//

#include "pch.h"
#include "Game.h"

Game::Game(SDL_Renderer *renderer)
  : font_{TTF_OpenFont(FONT_FILE, 24)}
  , snake_{nullptr}
  , field_(renderer, FIELD_FILE)
  , food_(renderer,FOOD_FILE)
  , score_(renderer)
  , renderer_{renderer}
  , font_color_{0, 0, 0, SDL_ALPHA_OPAQUE}
  , food_pos{0, 0}
  , pause_{false}
  , game_over_{false}
  , highscore_{0}
  , soundtrack_{nullptr} {
  food_.set_center(0, 0);
  food_.set_size(TILE_SIZE, TILE_SIZE);

  if (!font_)
    OnError(fmt::format("Couldn't load font \"{}\"", FONT_FILE));

  prng_.seed(time(nullptr));

  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

  filestream_.open("./resource/highscore", std::ios::in);
  if (filestream_.good()) {
    std::string score;
    std::getline(filestream_, score);
    try {
      Uint32 n_score = std::stoul(score);
      highscore_ = n_score;
    } catch (std::exception &ex) {
      OnError(ex.what());
    }

    filestream_.close();
  }

  soundtrack_ = Mix_LoadMUS(MUSIC_FILE);
  if (!soundtrack_)
    OnError(fmt::format("Couldn't load file \"{}\": {}", MUSIC_FILE, Mix_GetError()));
  Mix_PlayMusic(soundtrack_, -1);

  Restart();
}
Game::~Game() {
  TTF_CloseFont(font_);
  Mix_CloseAudio();

  filestream_.open("./resource/highscore", std::ios::out | std::ios::trunc);
  filestream_ << highscore_ << "\n";
  filestream_.close();
}

void Game::EndGame() {
  int max_length = 0;
  TTF_SizeText(font_, "Press 'r' to restart", &max_length, nullptr);

  SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(font_, fmt::format("Game over!\nScore: {}\nPress 'r' to restart", snake_->get_length()).c_str(), font_color_, max_length);
  score_.set_texture(&surf);
  game_over_ = true;

  if (snake_->get_length() > highscore_)
    highscore_ = snake_->get_length();
}

void Game::HandleEvent(SDL_Event *evt) {
  if (!pause_ && !game_over_) {
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
  if (!pause_ && !game_over_)
    snake_->Tick(ms);
}

void Game::Render() {
  field_.Render();

  food_.RenderAt(food_pos.x * TILE_SIZE, food_pos.y * TILE_SIZE);
  snake_->Render();

  if (!game_over_)
    score_.Render();
  else
    score_.RenderAt(WINDOW_SIZE_X / 2 - score_.get_size().x, WINDOW_SIZE_Y / 2 - score_.get_size().y);
}