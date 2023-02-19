#ifndef ENTITY_H 
#define ENTITY_H 

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t entity_t;

entity_t Entity_create();
bool Entity_is_alive(entity_t id);
void Entity_destroy(entity_t id);

#endif