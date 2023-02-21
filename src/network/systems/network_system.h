#ifndef NETWORK_SYSTEM_H
#define NETWORK_SYSTEM_H

#include <arpa/inet.h>

extern const in_port_t SERVER_PORT;

void network_start_server();
void network_start_client(const char* connection);

void network_physics_process(float);
void network_graphics_process(float);

#endif