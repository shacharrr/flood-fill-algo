#include "display.h"
#include "queue.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

uint32_t *color_buffer = NULL;
SDL_Texture *texture = NULL;

bool init_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    printf("Failed to initialize a SDL\n");
    return false;
  }

  window = SDL_CreateWindow("Flood fill", 0, 0, WIDTH, HEIGHT, 0);
  if (window == NULL) {
    printf("Failed to initialize a window\n");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL) {
    printf("Failed to initialize a renderer\n");
    return false;
  }

  color_buffer = (uint32_t *)calloc(WIDTH * HEIGHT, sizeof(uint32_t));
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
  if (texture == NULL) {
    printf("Failed to initialize a texture\n");
    return false;
  }

  return true;
}

void update_texture(void) {
  SDL_UpdateTexture(texture, NULL, color_buffer, WIDTH * 4);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void destroy_window(void) {
  free(color_buffer);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
}

void draw_pixel(int x, int y, uint32_t color) {
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    color_buffer[(y * WIDTH) + x] = color;
  }
}

uint32_t get_pixel(int x, int y) {
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    return color_buffer[(y * WIDTH) + x];
  }
  return 0;
}

void clear(uint32_t color) {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      draw_pixel(x, y, color);
    }
  }
}

void draw_line(int x1, int y1, int x2, int y2, uint32_t color) {
  // DDA
  int dx = x2 - x1;
  int dy = y2 - y1;
  float step;
  if (dx >= dy) {
    step = dx;
  } else {
    step = dy;
  }

  float x_increment = dx / step;
  float y_increment = dy / step;
  float x = x1;
  float y = y1;
  for (int i = 0; i <= step; i++) {
    draw_pixel(x, y, color);
    x += x_increment;
    y += y_increment;
  }
}

void flood_fill(int x, int y, uint32_t start_color, uint32_t color) {
  if (start_color == color) {
    return;
  }

  queue_t *q = init_queue(128);
  point_t p = {.x = x, .y = y};
  node_t *n = (node_t *)malloc(sizeof(node_t));
  n->p = p;
  n->next = NULL;
  enqueue(q, n);

  int range[] = {1, -1};
  int range_length = 2;

  while (!is_empty(q)) {
    n = dequeue(q);
    if (n == NULL) {
      continue;
    }
    p = n->p;

    x = p.x, y = p.y;
    draw_pixel(x, y, color);
    for (int i = 0; i < range_length; i++) {
      if (get_pixel(x, y + range[i]) == start_color) {
        draw_pixel(x, y + range[i], color);
        point_t new_point = {.x = x, .y = y + range[i]};
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node->p = new_point;
        new_node->next = NULL;
        enqueue(q, new_node);
      }
      if (get_pixel(x + range[i], y) == start_color) {
        draw_pixel(x + range[i], y, color);
        point_t new_point = {.x = x + range[i], .y = y};
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node->p = new_point;
        new_node->next = NULL;
        enqueue(q, new_node);
      }
    }
    free(n);
  }
  free_queue(q);
}
