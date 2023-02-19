#include "entity.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <containers/hashmap.h>

typedef struct Entity {
    entity_t id;
    bool is_alive;
} Entity;

Entity* entities = NULL;
size_t* entity_map;

size_t size_entities = 0;
const size_t starting_size = 32;

entity_t next_entity_id = 1;

entity_t Entity_create() {
    if (entities == NULL) {
        entities = malloc(sizeof(Entity) * starting_size);
        entity_map = malloc(sizeof(size_t) * starting_size);
    }
    for (size_t i = 0; i < size_entities; i++) {
        if (!entities[i].is_alive) {
            entities[i].id = next_entity_id;
            next_entity_id++;

            entities[i].is_alive = true;

            entity_map[entities[i].id] = i;
            return entities[i].id;
        }
    }

    return 0;
}

Entity* _Entity_get(entity_t id) {
    return &entities[entity_map[id]];
}

bool Entity_is_alive(entity_t id) {
    return _Entity_get(id)->is_alive;
}

void Entity_destroy(entity_t id) {
    _Entity_get(id)->is_alive = false;
}