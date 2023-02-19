#ifndef WINDOW_COMPONENT_H
#define WINDOW_COMPONENT_H

#include <SDL2/SDL.h>
#include <ecs/entity.h>

typedef struct {
    SDL_Window* window;
} window_component;

void window_component_init();

void* window_component_create(entity_t entity, void* data);
window_component* window_component_get(entity_t);
void window_component_destroy(entity_t, void* data);

void window_component_cleanup();

#endif