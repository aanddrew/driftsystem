#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

typedef void (*PhysicsFunc)(float);
typedef void (*GraphicsFunc)(float);

typedef enum {
    LOGGING_SYSTEM,
    WINDOW_SYSTEM,
    NUM_SYSTEMS
} SYSTEM_ID;

typedef struct System {
    SYSTEM_ID id;
    PhysicsFunc physics_process_func;
    PhysicsFunc graphics_process_func;
} System;

#include <game/systems/logging.h>
#include <client/graphics/systems/window_system.h>

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
};

#endif