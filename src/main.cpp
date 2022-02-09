#include "Game.h"
#include "misc.h"
#include "pch.h"

SDL_Window *g_window = nullptr;
SDL_Renderer *g_renderer = nullptr;

int main(int argc, char **argv) {
  atexit(
          []() {
            SDL_Quit();
            TTF_Quit();
            IMG_Quit();
            Mix_Quit();
          });

  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    OnError(fmt::format("Error whilst initialising: \"{}\"", SDL_GetError()));
  }
  if (TTF_Init()) {
    OnError(fmt::format("Error whilst initialising TTF: \"{}\"", TTF_GetError()));
  }
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    OnError(fmt::format("Error whilst initialising IMG: \"{}\"", IMG_GetError()));
  }

  int flags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
  if (Mix_Init(flags) != flags) {
    OnError(fmt::format("Error whilst initialising Mix: \"{}\"", Mix_GetError()));
  }

  g_window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_RESIZABLE);
  if (!g_window) {
    OnError(fmt::format("Error whilst creating window: \"{}\"", SDL_GetError()));
  }

  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!g_renderer) {
    OnError(fmt::format("Error whilst creating renderer: \"{}\"", SDL_GetError()));
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
  SDL_SetRenderDrawBlendMode(g_renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderSetLogicalSize(g_renderer, WINDOW_SIZE_X, WINDOW_SIZE_Y);

  SDL_Surface *icon = IMG_Load(ICON_FILE);

  if (!icon)
    OnError(fmt::format("Couldn't load texture \"{}\".", ICON_FILE));

  SDL_SetWindowIcon(g_window, icon);
  SDL_FreeSurface(icon);

  Game game(g_renderer);
  Uint64 ticks = SDL_GetTicks64();

  SDL_Event evt;
  bool running = true;
  while (running) {
    while (SDL_PollEvent(&evt)) {
      if (evt.type == SDL_QUIT) {
        running = false;
      } else if (evt.type == SDL_WINDOWEVENT) {
        switch (evt.window.event) {
          case SDL_WINDOWEVENT_CLOSE:
            running = false;
            break;

          case SDL_WINDOWEVENT_MINIMIZED:
            do {
              SDL_WaitEvent(&evt);
            } while (evt.type != SDL_WINDOWEVENT || evt.window.event != SDL_WINDOWEVENT_RESTORED);
            break;
        }
      } else if (evt.type == SDL_KEYDOWN) {
        switch (evt.key.keysym.sym) {
          case SDLK_F11:
            if (SDL_GetWindowFlags(g_window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
              SDL_SetWindowFullscreen(g_window, 0);
              SDL_SetWindowMouseGrab(g_window, SDL_FALSE);
            } else {
              SDL_SetWindowFullscreen(g_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
              SDL_SetWindowMouseGrab(g_window, SDL_TRUE);
            }
            break;

          default:
            game.HandleEvent(&evt);
            break;
        }
      }
    }

    Uint64 n = SDL_GetTicks64();
    game.Tick(n - ticks);
    ticks = n;

    SDL_RenderClear(g_renderer);

    game.Render();

    SDL_RenderPresent(g_renderer);
  }

  SDL_DestroyRenderer(g_renderer);
  SDL_DestroyWindow(g_window);

  return EXIT_SUCCESS;
}