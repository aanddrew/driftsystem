#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include <ecs/entity.h>

int main() {
    uint32_t handle = Entity_create();
    return 0;
}

/*
int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow("driftsystem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to open window: %s\n", SDL_GetError());
        exit(1);
    }

    bool running = true;
    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        //render
    }

    SDL_Delay(100);
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
    return 0;
}*/