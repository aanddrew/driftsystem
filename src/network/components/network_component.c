#include "network_component.h"

#include <ecs/component.h>
#include <stdlib.h>

const network_peer_id NETWORK_SERVER_ID = 0;

void network_component_init() { }

void* network_component_create(entity_t entity, void* data) {
    (void)(entity);

    network_component* component = malloc(sizeof(network_component));
    component->owner = NETWORK_SERVER_ID;
    if (data != NULL) {
        component->owner = ((network_component*)data)->owner;
    }

    return component;
}
network_component* network_component_get(entity_t entity) {
    return component_get(entity, COMPONENT_NETWORK);
}

void network_component_destroy(entity_t entity, void* data) {
    (void)(entity);
    free(data);
}

void network_component_cleanup() {}