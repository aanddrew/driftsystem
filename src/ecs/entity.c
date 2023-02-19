#include "entity.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <containers/hashmap.h>

typedef struct entity {
    entity_t id;
    bool is_alive;
} entity;
entity_t next_entity_id = 1;

struct hashmap* entity_map = NULL;

//for hashmap
#pragma GCC diagnostic ignored "-Wunused-parameter"
int entity_compare(const void* a, const void* b, void* udata) {
    return ((entity*) a)->id == ((entity*) b)->id;
}
uint64_t entity_hash(const void* item, uint64_t seed0, uint64_t seed1) {
    return hashmap_sip(&((entity*) item)->id, sizeof(entity_t), seed0, seed1);
}

entity_t entity_create() {
    if (entity_map == NULL) {
        entity_map = hashmap_new(sizeof(entity), 0, 0, 0, entity_hash, entity_compare, NULL, NULL);
    }

    entity new = (entity) {
        .id = next_entity_id,
        .is_alive = true
    };
    next_entity_id++;

    hashmap_set(entity_map, &new);
    return new.id;
}

entity* _entity_get(entity_t id) {
    return hashmap_get(entity_map, &(entity){ .id=id });
}

bool entity_is_alive(entity_t id) {
    return _entity_get(id)->is_alive;
}

void entity_destroy(entity_t id) {
    _entity_get(id)->is_alive = false;
}