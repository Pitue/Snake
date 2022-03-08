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
struct Position {
  int x, y;

  Position(int x, int y)
          : x{x}
          , y{y} {

  }

  inline bool operator==(const Position& other) const {
    return (x == other.x) && (y == other.y);
  }
};


bool IsVertical(Direction d);
bool IsHorizontal(Direction d);
bool IsIncreasing(Direction d);
bool IsDecreasing(Direction d);

#define WINDOW_SIZE_X 600
#define WINDOW_SIZE_Y WINDOW_SIZE_X
#define TILE_SIZE 20
#define BORDER_SIZE

#define POWERUP_TIME (Uint64)5000
#define AS_SECONDS(x) ((double)(x) / 1000.0)
#define SPEED (Uint64)80

#define FIELD_SIZE_REL 30

#define FONT_FILE "./resource/arial.ttf"

#define FIELD_FILE "./resource/field.png"
#define SNAKE_HEAD_FILE "./resource/snake_head.png"
#define SNAKE_FILE "./resource/snake.png"
#define FOOD_FILE "./resource/food.png"

#define SFX_EATING_FILE "./resource/food.mp3"
#define SFX_DYING_FILE "./resource/died.mp3"
#define SFX_POWERUP_ON_FILE "./resource/powerup_on.mp3"
#define SFX_POWERUP_OFF_FILE "./resource/powerup_off.mp3"

#define ICON_FILE "./resource/icon.png"

Mix_Chunk *LoadSFX(const char *file);

#endif//SNAKE_MISC_H
