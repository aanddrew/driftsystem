#ifndef ENTITY_H 
#define ENTITY_H 

#include <stdint.h>
#include <stdbool.h>

typedef struct Entity {
    uint32_t id;
    char* name;
    bool is_alive;
} Entity;

uint32_t Entity_create();
uint32_t Entity_create_named(const char* name);
Entity* Entity_get(uint32_t id);

#endif