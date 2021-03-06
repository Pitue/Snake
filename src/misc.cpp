//
// Created by marc on 28.01.22.
//

#include "pch.h"
#include "misc.h"

void OnError(std::string &&str) {
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", str.c_str(), nullptr);
  exit(EXIT_FAILURE);
}

bool IsVertical(Direction d) {
  return d == Direction::UP || d == Direction::DOWN;
}
bool IsHorizontal(Direction d) {
  return d == Direction::LEFT || d == Direction::RIGHT;
}
bool IsIncreasing(Direction d) {
  return d == Direction::RIGHT || d == Direction::DOWN;
}
bool IsDecreasing(Direction d) {
  return d == Direction::LEFT || d == Direction::UP;
}

Mix_Chunk *LoadSFX(const char *file) {
  Mix_Chunk *temp = Mix_LoadWAV(file);
  if (!temp)
    OnError(fmt::format("Couldn't load file \"{}\": {}", file, Mix_GetError()).c_str());
  return temp;
}
