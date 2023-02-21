#include "window_system.h"

#include <stdio.h>

#include <ecs/component.h>
#include <ecs/entity.h>

void window_graphics_process(float delta) {
    (void)(delta);

    component_bits(query);
    component_bits_zero(query);
    component_bits_set(query, COMPONENT_WINDOW, true);

    entity_t* entities = component_query(query);
    if (entities == NULL) {
        return;
    }
    printf("Found a window entity!\n");
}

void window_physics_process(float delta) {
    (void)(delta);
}