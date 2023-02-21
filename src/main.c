#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/system.h>

#include <client/graphics/window.h>
#include <server/server.h>

#include <network/systems/network_system.h>

#include <GL/glew.h>

const float PHYSICS_DELTA = (1.0f / 64.0);

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--server")) {
            return servermain(argc, argv);
        }
        else if (!strcmp(argv[i], "--client")) {
            network_start_client("localhost");
        }
    }

    components_init();

    window_create();

    bool running = true;
    clock_t then = clock();
    float physics_time_accumulated = 0.0f;

    while (running) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        //per frame processing
        clock_t now = clock();
        float dt = ((float) now - then)/CLOCKS_PER_SEC;
        systems_all_graphics_process(dt);

        //fixed delta processing
        physics_time_accumulated += dt;
        while (physics_time_accumulated > PHYSICS_DELTA) {
            systems_all_physics_process(PHYSICS_DELTA);
            physics_time_accumulated -= PHYSICS_DELTA;
        }

        then = clock();
    }

    window_destroy();
    components_cleanup();
    return 0;
}