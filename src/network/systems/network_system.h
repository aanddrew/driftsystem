#ifndef NETWORK_SYSTEM_H
#define NETWORK_SYSTEM_H

#include <arpa/inet.h>
#include <containers/cvector.h>

extern const in_port_t SERVER_PORT;

typedef uint32_t network_id;

typedef struct {
    cvector_vector_type(uint8_t) data;
    network_id sender;
} packet;

void network_start_server();
void network_start_client(const char* connection);

void network_physics_process(float);
void network_graphics_process(float);

#endif