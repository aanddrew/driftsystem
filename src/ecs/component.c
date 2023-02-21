#include "component.h"

#include <containers/hashmap.h>
#include <containers/cvector.h>

typedef struct {
    component_t id;
    ComponentInitFunc init_func;
    ComponentCleanupFunc cleanup_func;
    ComponentCreateFunc create_func;
    ComponentDestroyFunc destroy_func;
} component_store;

#include <client/graphics/components/window_component.h>
#include <client/graphics/components/shader_component.h>
#include <network/components/network_component.h>

component_store components[NUM_COMPONENTS] = {
    [COMPONENT_NONE] = {
        .id = COMPONENT_NONE,
        .init_func = NULL,
        .cleanup_func = NULL,
        .create_func = NULL,
        .destroy_func = NULL
    },
    [COMPONENT_WINDOW] = {
        .id = COMPONENT_WINDOW,
        .init_func = window_component_init,
        .cleanup_func = window_component_cleanup,
        .create_func = window_component_create,
        .destroy_func = window_component_destroy,
    },
    [COMPONENT_SHADER] = {
        .id = COMPONENT_SHADER,
        .init_func = shader_component_init,
        .cleanup_func = shader_component_cleanup,
        .create_func = shader_component_create,
        .destroy_func = shader_component_destroy,
    },
    [COMPONENT_NETWORK] = {
        .id = COMPONENT_NETWORK,
        .init_func = network_component_init,
        .cleanup_func = network_component_cleanup,
        .create_func = network_component_create,
        .destroy_func = network_component_destroy,
    }
};
typedef struct {
    entity_t entity;
    component_bits(bits);
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
struct hashmap* query_cache;

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
    hashmap_free(query_cache);
    entity_component_map = NULL;
    for (size_t i = 0; i < NUM_COMPONENTS; i++) {
        if (components[i].cleanup_func != NULL) {
            components[i].cleanup_func();
        }
    }
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

void empty_query_cache() {
    if (query_cache != NULL) {
        hashmap_clear(query_cache, false);
    }
}

void component_add(entity_t entity, component_t type, void* data) {
    empty_query_cache();
    entity_components* ec = get_components(entity);
    component_bits_set(ec->bits, type, 1);
    ec->component_data[type] = components[type].create_func(entity, data);
}

void* component_get(entity_t entity, component_t type) {
    entity_components* ec = get_components(entity);
    return ec->component_data[type];
}

void component_remove(entity_t entity, component_t type) {
    empty_query_cache();
    entity_components* ec = get_components(entity);
    component_bits_set(ec->bits, type, 0);
    components[type].destroy_func(entity, ec->component_data[type]);
}

void component_list(entity_t entity, component_bits(out)) {
    entity_components* ec = get_components(entity);
    for (size_t i = 0; i < COMPONENT_BITS_LENGTH; i++) {
        out[i] = ec->bits[i];
    }
}


typedef struct {
    component_bits(query);
    cvector_vector_type(entity_t) vector;
} query_result;

struct hashmap* query_cache = NULL;

int query_compare(const void* a, const void* b, void* udata) {
    (void)(udata);
    for (size_t i = 0; i < COMPONENT_BITS_LENGTH; i++) {
        if (((query_result*) a)->query[i] != ((query_result*) b)->query[i]) {
            return false;
        }
    }
    return true;
}
uint64_t query_hash(const void* item, uint64_t seed0, uint64_t seed1) {
    return hashmap_sip(&((query_result*) item)->query, COMPONENT_BITS_SIZE, seed0, seed1);
}

void query_free(void* data) {
    query_result* query = (query_result*) data;
    cvector_free(query->vector);
}

bool entity_query_iter(const void* item, void* udata) {
    entity_components* ec = (entity_components*) item;
    query_result* result = (query_result*) udata;

    for (size_t i = 0; i < COMPONENT_BITS_LENGTH; i++) {
        if ((ec->bits[i] & result->query[i]) != result->query[i]) {
            return true;
        }
    }

    cvector_push_back(result->vector, ec->entity);

    return true;
}

entity_t* component_query(component_bits(query)) {
    if (query_cache == NULL) {
        query_cache = hashmap_new(
            sizeof(query_result), 
            0, 
            0, 
            0, 
            query_hash, 
            query_compare, 
            query_free, 
            NULL);
    }

    query_result result = {
       .vector = NULL,
    };
    component_bits_zero(result.query);
    component_bits_copy(query, result.query);

    query_result* found_result = hashmap_get(query_cache, &result);
    if (found_result != NULL) {
        return found_result->vector;
    }

    hashmap_scan(entity_component_map, entity_query_iter, query);

    hashmap_set(query_cache, &result);

    return result.vector;
}