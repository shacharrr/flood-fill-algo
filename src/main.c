#include "display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

enum mode { PAINT_BRUSH, FILL_BUCKET };

bool is_running = true;
int mouse_x = 0, mouse_y = 0;
bool clicked = false;
int current_mode = PAINT_BRUSH;

void setup(void) { clear(0xFFFFFFFF); }

void handle_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  SDL_GetMouseState(&mouse_x, &mouse_y);
  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
  case SDL_KEYUP:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      is_running = false;
    }
    if (event.key.keysym.sym == SDLK_p) {
      current_mode = PAINT_BRUSH;
    }
    if (event.key.keysym.sym == SDLK_b) {
      current_mode = FILL_BUCKET;
    }
    break;
  case SDL_MOUSEBUTTONDOWN:
    clicked = true;
    break;
  case SDL_MOUSEBUTTONUP:
    clicked = false;
    break;
  }
}

void draw(void) {
  if (clicked) {
    if (current_mode == PAINT_BRUSH) {
      for (int i = -1; i < 1; i++) {
        draw_pixel(mouse_x + i, mouse_y, 0xFF00FF00);
        draw_pixel(mouse_x, mouse_y + i, 0xFF00FF00);
      }
    }
    if (current_mode == FILL_BUCKET) {
      uint32_t start_color = get_pixel(mouse_x, mouse_y);
      flood_fill(mouse_x, mouse_y, start_color, 0xFFFF0000);
    }
  }

  update_texture();
  SDL_RenderPresent(renderer);
}

int main(int argc, char **argv) {
  init_window();
  setup();
  while (is_running) {
    handle_input();
    draw();
  }
  destroy_window();

  return 0;
}
