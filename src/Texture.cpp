//
// Created by marc on 28.01.22.
//

#include "pch.h"
#include "Texture.h"

Texture::Texture(SDL_Renderer *renderer)
        : texture_{nullptr}
        , flip_{SDL_FLIP_NONE}
        , center_{0,0}
        , renderer_{renderer}
        , angle_{0.0} {
}
Texture::Texture(SDL_Renderer *renderer, const char *file)
  : Texture(renderer) {
  Load(file);
}

Texture::~Texture() {
  SDL_DestroyTexture(texture_);
}

void Texture::Load(const char *file) {
  texture_ = IMG_LoadTexture(renderer_, file);
  if (!texture_)
    OnError(fmt::format("Couldn't load texture \"{}\"", file));

  AdjustSize();
}

void Texture::Render() {
  if (!texture_)
    return;

  SDL_Rect dest {0, 0, size_.x, size_.y };
  SDL_RenderCopyEx(renderer_, texture_, nullptr, &dest, angle_, &center_, flip_);
}
void Texture::RenderAt(int x, int y) {
  if (!texture_)
    return;

  SDL_Rect dest {x, y, size_.x, size_.y };
  SDL_RenderCopyEx(renderer_, texture_, nullptr, &dest, angle_, &center_, flip_);
}
