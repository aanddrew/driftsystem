#include "window_component.h"

#include <ecs/component.h>
#include <containers/hashmap.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <stdio.h>

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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    glewExperimental = true;
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glew_error));
        exit(1);
    }

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