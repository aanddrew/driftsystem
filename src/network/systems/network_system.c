#include "network_system.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

#include <network/components/network_component.h>
#include <ecs/component.h>
#include <ecs/entity.h>

#include <containers/cvector.h>

const in_port_t SERVER_PORT = 8323;

typedef int socket_fd;

typedef struct {
    network_peer_id id;
} network_peer;

socket_fd tcp;
socket_fd udp;

void network_start_server() {

}

void network_start_client(const char* connection) {
    tcp = socket(AF_INET, SOCK_DGRAM, 0);
    udp = socket(AF_INET, SOCK_DGRAM, 0);
    //udp = socket(AF_N, SOCK_DGRAM, IPPROTO_UDP);

    if (tcp < 0 || udp < 0) {
        printf("Could not create client sockets %s!\n", strerror(errno));
        exit(1);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(connection);

    if(bind(tcp, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        printf("Couldn't bind tcp socket!\n");
        exit(1);
    }
    server_address.sin_port = htons(SERVER_PORT + 1);
    if(bind(udp, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        printf("Couldn't bind udp socket!\n");
        exit(1);
    }
    printf("Created client!\n");
}

void network_physics_process(float delta) {
    (void)(delta);
}

void network_graphics_process(float delta) { 
    (void)(delta);
    return;

    component_bits(query);
    component_bits_zero(query);
    component_bits_set(query, COMPONENT_NETWORK, true);

    entity_t* entities = NULL; //component_query(query);
    if (entities == NULL) {
        return;
    }
    
    size_t num_entities = 0;//cvector_size(entities);

    for (size_t i = 0; i < num_entities; i++) {
        printf("%d is a network entity!\n", entities[i]);
    }
}