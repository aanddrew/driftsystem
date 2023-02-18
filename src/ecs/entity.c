#include "entity.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Entity* entities = NULL;
size_t* entity_map;

size_t size_entities = 0;
const size_t starting_size = 32;

uint32_t next_entity_id = 1;

uint32_t Entity_create() {
    return Entity_create_named(NULL);
}

uint32_t Entity_create_named(const char* name) {
    if (entities == NULL) {
        entities = malloc(sizeof(Entity) * starting_size);
        entity_map = malloc(sizeof(size_t) * starting_size);
    }
    for (size_t i = 0; i < size_entities; i++) {
        if (!entities[i].is_alive) {
            if (entities[i].name != NULL) {
                free(entities[i].name);
                entities[i].name = NULL;
            }
            if (name != NULL) {
                entities[i].name = malloc(sizeof(char) * strlen(name) + 1);
                strcpy(entities[i].name, name);
            }
            entities[i].id = next_entity_id;
            next_entity_id++;
            entities[i].is_alive = true;

            entity_map[next_entity_id] = i;
        }
    }

    return 0;
}

Entity* Entity_get(uint32_t id) {
    return &entities[entity_map[id]];
}
