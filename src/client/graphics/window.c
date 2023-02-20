#include "window.h"

#include <ecs/component.h>

entity_t window;

entity_t window_create() {
    entity_t window = entity_create();
    component_add(window, COMPONENT_WINDOW, NULL);
    return window;
}

void window_destroy() {
    component_remove(window, COMPONENT_WINDOW);
}
