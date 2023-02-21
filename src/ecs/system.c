#include <ecs/system.h>

#include <game/systems/logging.h>
#include <client/graphics/systems/window_system.h>
#include <network/systems/network_system.h>

#include <stdlib.h>

System systems[NUM_SYSTEMS] = {
    [LOGGING_SYSTEM] = {
        .id = LOGGING_SYSTEM, 
        .physics_process_func = logging_physics_process,
        .graphics_process_func = logging_graphics_process,
    },
    [WINDOW_SYSTEM] = {
        .id = WINDOW_SYSTEM,
        .physics_process_func = window_physics_process,
        .graphics_process_func = window_graphics_process,
    },
    [NETWORK_SYSTEM] = {
        .id = NETWORK_SYSTEM,
        .physics_process_func = network_physics_process,
        .graphics_process_func = network_graphics_process,
    }
};

void systems_all_graphics_process(float delta) {
    for (size_t i = 0; i < NUM_SYSTEMS; i++) {
        if (systems[i].graphics_process_func != NULL) {
            systems[i].graphics_process_func(delta);
        }
    }
}

void systems_all_physics_process(float delta) {
    for (size_t i = 0; i < NUM_SYSTEMS; i++) {
        if (systems[i].physics_process_func != NULL) {
            systems[i].physics_process_func(delta);
        }
    }
}