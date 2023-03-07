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
typedef uint64_t COMPONENT_BITS_TYPE;
#define COMPONENT_BITS_LENGTH NUM_COMPONENTS / sizeof(COMPONENT_BITS_TYPE) + 1
typedef COMPONENT_BITS_TYPE component_bits[COMPONENT_BITS_LENGTH];

extern void component_bits_zero(component_bits bits);
extern void component_bits_set(component_bits array, uint32_t component, bool value);
extern void component_bits_copy(component_bits src, component_bits dest);
extern bool component_bits_get(component_bits array, uint32_t i);

void components_init();
void components_cleanup();

void component_add(entity_t entity, component_t type, void* data);
void* component_get(entity_t entity, component_t type);

void component_remove(entity_t entity, component_t type);
void component_list(entity_t entity, component_bits(out));

cvector_vector_type(entity_t) component_query(component_bits(query));

#endif