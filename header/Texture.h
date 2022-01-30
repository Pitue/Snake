//
// Created by marc on 28.01.22.
//

#ifndef SNAKE_TEXTURE_H
#define SNAKE_TEXTURE_H

#include "pch.h"
#include "misc.h"

class Texture {
  SDL_Texture *texture_{};
  SDL_Point center_{};
  SDL_Point size_{};
  SDL_RendererFlip flip_;
  SDL_Renderer *renderer_{};
  double angle_;

  inline void AdjustSize() {
    SDL_QueryTexture(texture_, nullptr, nullptr, &size_.x, &size_.y);
    center_.x = size_.x / 2;
    center_.y = size_.y / 2;
  }
public:
  explicit Texture(SDL_Renderer *renderer);
  Texture(SDL_Renderer *renderer, const char *file);
  ~Texture();

  void Load(const char *file);

  inline void set_center(int x, int y) {
    center_ = {x, y};
  }
  inline void set_size(int x, int y) {
    size_ = {x, y};
  }
  inline void set_texture(SDL_Texture *text) {
    texture_ = text;
  }
  inline void set_texture(SDL_Surface **surf) {
    texture_ = SDL_CreateTextureFromSurface(renderer_, *surf);
    SDL_FreeSurface(*surf);
    surf = nullptr;
    AdjustSize();
  }
  inline void set_rotation(double angle) {
    angle_ = angle;
  }

  [[nodiscard]] inline SDL_Point get_center() const {
    return center_;
  }

  void Render();
  void RenderAt(int x, int y);
};


#endif//SNAKE_TEXTURE_H
