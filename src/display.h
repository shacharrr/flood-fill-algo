#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern uint32_t *color_buffer;
extern SDL_Texture *texture;

bool init_window(void);
void update_texture(void);
void destroy_window(void);

void draw_pixel(int x, int y, uint32_t color);
uint32_t get_pixel(int x, int y);
void clear(uint32_t color);
void draw_line(int x1, int y1, int x2, int y2, uint32_t color);
void flood_fill(int x, int y, uint32_t start_color, uint32_t color);

#endif // !DISPLAY_H
