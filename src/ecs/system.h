#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

typedef void (*PhysicsFunc)(float);
typedef void (*GraphicsFunc)(float);

typedef enum {
    LOGGING_SYSTEM,
    WINDOW_SYSTEM,
    NETWORK_SYSTEM,
    NUM_SYSTEMS
} SYSTEM_ID;

typedef struct System {
    SYSTEM_ID id;
    PhysicsFunc physics_process_func;
    PhysicsFunc graphics_process_func;
} System;

void systems_all_graphics_process(float delta);
void systems_all_physics_process(float delta);

#endif