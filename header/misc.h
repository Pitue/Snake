//
// Created by marc on 28.01.22.
//

#ifndef SNAKE_MISC_H
#define SNAKE_MISC_H

void OnError(std::string &&str);

enum class Direction : uint_fast8_t {
  UP = 0,
  RIGHT,
  LEFT,
  DOWN
};
bool IsVertical(Direction d);
bool IsHorizontal(Direction d);
bool IsIncreasing(Direction d);
bool IsDecreasing(Direction d);

#define WINDOW_SIZE_X 600
#define WINDOW_SIZE_Y WINDOW_SIZE_X
#define TILE_SIZE 20

#define SPEED (Uint64)80
#define FIELD_SIZE_REL 30

#define FONT_FILE "./resource/arial.ttf"
#define FIELD_FILE "./resource/rwe.png"
#define SNAKE_HEAD_FILE "./resource/snake_heasd.png"
#define SNAKE_FILE "./resource/snake.png"
#define FOOD_FILE "./resource/food.png"

#define MUSIC_FILE "./resource/music.mp3"

#define SFX_EATING_FILE "./resource/food.mp3"
#define SFX_DYING_FILE "./resource/died.wav"


struct Position {
  double x, y;
};

#endif//SNAKE_MISC_H
