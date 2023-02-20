#include "window_component.h"

#include <ecs/component.h>

#include <containers/hashmap.h>

void window_component_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL: %s\n", SDL_GetError());
        exit(1);
    }
}

void* window_component_create(entity_t entity, void* data) {
    (void)(data);
    (void)(entity);

    window_component* component = malloc(sizeof(window_component));

    SDL_Window* window = SDL_CreateWindow("driftsystem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to open window: %s\n", SDL_GetError());
        exit(1);
    }
    component->window = window;

    return component;
}

window_component* window_component_get(entity_t entity) {
    return (window_component*) component_get(entity, COMPONENT_WINDOW);
}

void window_component_destroy(entity_t entity, void* data) {
    (void)(entity);
    if (data == NULL) {
        return;
    }
    SDL_DestroyWindow(((window_component*)data)->window);
    free(data);
}

void window_component_cleanup() {
    SDL_Quit();
}