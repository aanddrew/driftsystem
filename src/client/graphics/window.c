#include "window.h"

#include <ecs/component.h>
#include <client/graphics/components/window_component.h>
#include <game/systems/logging.h>

#include <stdio.h>

entity_t window;

entity_t window_create() {
    entity_t window = entity_create();

    component_add(window, COMPONENT_WINDOW, NULL);

    return window;
}

void window_destroy() {
    component_remove(window, COMPONENT_WINDOW);
}

SDL_Window* window_get() {
    component_bits bits;
    component_bits_zero(bits);
    component_bits_set(bits, COMPONENT_WINDOW, true);
    cvector_vector_type(entity_t) query = component_query(bits);
    if (cvector_size(query) < 1) {
        LOG_ERROR("Could not find window entity!\n");
        exit(1);
    }

    window_component* comp = component_get(query[0], COMPONENT_WINDOW);
    if (comp == NULL) {
        LOG_ERROR("Error, could not retrieve window component\n");
        exit(1);
    }
    return comp->window;
}