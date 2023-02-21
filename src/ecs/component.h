#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"
#include <stddef.h>

#include <containers/cvector.h>

typedef void* (*ComponentCreateFunc)(entity_t, void*);
typedef void (*ComponentDestroyFunc)(entity_t, void*);
typedef void (*ComponentInitFunc)();
typedef void (*ComponentCleanupFunc)();

typedef enum {
    COMPONENT_NONE,
    COMPONENT_WINDOW,
    COMPONENT_SHADER,
    COMPONENT_NETWORK,
    COMPONENT_MODEL,
    COMPONENT_POSITION,
    COMPONENT_VELOCITY,
    NUM_COMPONENTS
} component_t;

//bit array - one bit per component - one array per entity
typedef uint32_t COMPONENT_BITS_TYPE;
#define COMPONENT_BITS_LENGTH NUM_COMPONENTS / sizeof(COMPONENT_BITS_TYPE) + 1
#define COMPONENT_BITS_SIZE   NUM_COMPONENTS * sizeof(COMPONENT_BITS_TYPE)
#define component_bits(name) COMPONENT_BITS_TYPE name[COMPONENT_BITS_LENGTH]
#define component_bits_zero(bits) for (size_t i = 0; i < COMPONENT_BITS_LENGTH; i++) { bits[i] = 0; }
#define component_bits_copy(src, dest) for (size_t i = 0; i < COMPONENT_BITS_LENGTH; i++) { dest[i] = src[i]; }
#define component_bits_set(array, component, value) array[component / sizeof(COMPONENT_BITS_TYPE)] |= !!(value) << (component % sizeof(COMPONENT_BITS_TYPE))
#define component_bits_get(array, i) (bool) (array[i / sizeof(COMPONENT_BITS_TYPE)] >> (i % sizeof(COMPONENT_BITS_TYPE)) & 0x1)

void components_init();
void components_cleanup();

void component_add(entity_t entity, component_t type, void* data);
void* component_get(entity_t entity, component_t type);

void component_remove(entity_t entity, component_t type);
void component_list(entity_t entity, component_bits(out));

cvector_vector_type(entity_t) component_query(component_bits(query));

#endif