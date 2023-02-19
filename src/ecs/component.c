#include "component.h"

#include <containers/hashmap.h>

typedef struct {
    component_t id;
    ComponentInitFunc init_func;
    ComponentCreateFunc create_func;
    ComponentDestroyFunc destroy_func;
} component_store;

#include <client/gui/graphics/components/window_component.h>

component_store components[NUM_COMPONENTS] = {
    [COMPONENT_NONE] = {
        .id = COMPONENT_NONE,
        .init_func = NULL,
        .create_func = NULL,
        .destroy_func = NULL
    },
    [COMPONENT_WINDOW] = {
        .id = COMPONENT_WINDOW,
        .init_func = window_component_init,
        .create_func = window_component_create,
        .destroy_func = window_component_destroy,
    }
};
typedef struct {
    entity_t entity;
    component_bits_arg(bits);
    void* component_data[NUM_COMPONENTS];
} entity_components;

void entity_components_free(void* data) {
    entity_components* ec = (entity_components*) data;
    for (size_t i = 0; i < NUM_COMPONENTS; i++) {
        if (ec->component_data[i] != NULL) {
            components[i].destroy_func(ec->entity, ec->component_data[i]);
        }
    }
}

struct hashmap* entity_component_map = NULL;

//for hashmap
#pragma GCC diagnostic ignored "-Wunused-parameter"
int entity_component_compare(const void* a, const void* b, void* udata) {
    return ((entity_components*) a)->entity == ((entity_components*) b)->entity;
}
uint64_t entity_component_hash(const void* item, uint64_t seed0, uint64_t seed1) {
    return hashmap_sip(&((entity_components*) item)->entity, sizeof(entity_components), seed0, seed1);
}

void components_init() {
    for (size_t i = 0; i < NUM_COMPONENTS; i++) {
        if (components[i].init_func != NULL) {
            components[i].init_func();
        }
    }

    if (entity_component_map == NULL) {
        entity_component_map = hashmap_new(
            sizeof(entity_components), 
            0, 
            0, 
            0, 
            entity_component_hash, 
            entity_component_compare, 
            entity_components_free, 
            NULL);
    }
}

void components_cleanup() {
    hashmap_free(entity_component_map);
    entity_component_map = NULL;
}

entity_components* get_components(entity_t entity) {
    entity_components* ec = hashmap_get(entity_component_map, &(entity_components){.entity = entity});
    if (ec == NULL) {
        ec = (entity_components*) malloc(sizeof(entity_components));
        for (size_t i = 0; i < NUM_COMPONENTS; i++) {
            component_bits_set(ec->bits, i, 0);
            ec->component_data[i] = NULL;
        }
    }
    return ec;
}

void component_add(entity_t entity, component_t type, void* data) {
    entity_components* ec = get_components(entity);
    component_bits_set(ec->bits, type, 1);
    ec->component_data[type] = components[type].create_func(entity, data);
}

void* component_get(entity_t entity, component_t type) {
    entity_components* ec = get_components(entity);
    return ec->component_data[type];
}

void component_remove(entity_t entity, component_t type) {
    entity_components* ec = get_components(entity);
    component_bits_set(ec->bits, type, 0);
    components[type].destroy_func(entity, ec->component_data[type]);
}

void component_list(entity_t entity, component_bits_arg(out)) {
    entity_components* ec = get_components(entity);
    for (size_t i = 0; i < COMPONENT_BITS_LENGTH; i++) {
        out[i] = ec->bits[i];
    }
}

