#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"
#include <stddef.h>

typedef void* (*ComponentCreateFunc)(entity_t, void*);
typedef void (*ComponentDestroyFunc)(entity_t, void*);
typedef void (*ComponentInitFunc)();
typedef void (*ComponentCleanupFunc)();

typedef enum {
    COMPONENT_NONE,
    COMPONENT_WINDOW,
    COMPONENT_SHADER,
    COMPONENT_MODEL,
    COMPONENT_POSITION,
    COMPONENT_VELOCITY,
    NUM_COMPONENTS
} component_t;

//bit array - one bit per component - one array per entity
typedef uint32_t COMPONENT_BITS_TYPE;
#define COMPONENT_BITS_LENGTH NUM_COMPONENTS / sizeof(COMPONENT_BITS_TYPE) + 1
#define component_bits COMPONENT_BITS_TYPE[COMPONENT_BITS_LENGTH];
#define component_bits_arg(name) COMPONENT_BITS_TYPE name[COMPONENT_BITS_LENGTH]
#define component_bits_set(array, i, value) array[i / sizeof(COMPONENT_BITS_TYPE)] &= 0x1 >> value
#define component_bits_get(array, i) (bool) (array[i / sizeof(COMPONENT_BITS_TYPE)] << (i % sizeof(COMPONENT_BITS_TYPE)) & 0x1)

void components_init();
void components_cleanup();

void component_add(entity_t entity, component_t type, void* data);
void* component_get(entity_t entity, component_t type);

void component_remove(entity_t entity, component_t type);
void component_list(entity_t entity, component_bits_arg(out));

#endif