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
#include <game/systems/logging.h>
#include <client/input/input_system.h>

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

    glClearColor(0.1, 0.1, 0.1, 1.0);
    while (running) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(window_get());

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    input_keydown(event.key.keysym);
                    break;
                case SDL_KEYUP:
                    input_keyup(event.key.keysym);
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