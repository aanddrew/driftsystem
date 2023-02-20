#ifndef SHADER_COMPONENT_H
#define SHADER_COMPONENT_H

#include <stddef.h>
#include <ecs/entity.h>

typedef enum {
    SHADER_NONE,
    SHADER_DEFAULT,
    NUM_SHADERS
} shader_type;

typedef struct {
    const char* vertex_file_name;
    char* vertex_file_contents;
    size_t vertex_file_length;

    const char* fragment_file_name;
    char* fragment_file_contents;
    size_t fragment_file_length;
} shader;

typedef struct {
    shader* shader;
} shader_component;

void shader_component_init();

void* shader_component_create(entity_t entity, void* data);
shader_component* shader_component_get(entity_t);
void shader_component_destroy(entity_t, void* data);

void shader_component_cleanup();

#endif