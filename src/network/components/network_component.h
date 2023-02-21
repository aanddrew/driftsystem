#ifndef NETWORK_COMPONENT_H
#define NETWORK_COMPONENT_H

#include <stdint.h>
#include <ecs/entity.h>

typedef uint32_t network_peer_id;

extern const network_peer_id NETWORK_SERVER_ID;

typedef struct {
    network_peer_id owner;
} network_component;

void network_component_init();

void* network_component_create(entity_t entity, void* data);
network_component* network_component_get(entity_t);
void network_component_destroy(entity_t, void* data);

void network_component_cleanup();

#endif