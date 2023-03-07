#ifndef WINDOW_H
#define WINDOW_H

#include <ecs/entity.h>
#include <SDL2/SDL.h>

entity_t window_create();
void window_destroy();
SDL_Window* window_get();

#endif