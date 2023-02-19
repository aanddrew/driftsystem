#include <ecs/system.h>

typedef struct System {
    uint32_t id;
    PhysicsFunc physics_process_func;
    PhysicsFunc graphics_process_func;
} System;
