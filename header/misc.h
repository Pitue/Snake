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
#define FONT_FILE "./resource/arial.ttf"

#define SPEED (Uint64)80
#define FIELD_SIZE_REL 30

struct Position {
  double x, y;
};

#endif//SNAKE_MISC_H
