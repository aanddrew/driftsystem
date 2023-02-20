#include "shader_component.h"

#include <ecs/component.h>

#include <stdio.h>
#include <stdlib.h>

shader shaders[NUM_SHADERS] = {
    [SHADER_NONE] = {
        .vertex_file_name = NULL,
        .fragment_file_name = NULL
    },
    [SHADER_DEFAULT] = {
        .vertex_file_name = "assets/shaders/vertex.glsl", 
        .fragment_file_name="assets/shaders/fragment.glsl"
    },
};

void file_to_string(const char* filename, char** buffer, size_t* length) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fseek(file, 0, SEEK_END);
        *length = ftell(file);
        fseek(file, 0, SEEK_SET);

        *buffer = malloc(*length);
        fread(*buffer, 1, *length, file);

        fclose(file);
    }
    else {
        printf("Could not read file '%s'\n", filename);
        exit(1);
    }
}

void shader_component_init() { 
    for (size_t i = 0; i < NUM_SHADERS; i++) {
        shader* shader = &shaders[i];
        if (shader->vertex_file_name == NULL) {
            shader->vertex_file_contents = NULL;
            shader->vertex_file_length = 0;
        }
        else {
            file_to_string(shader->vertex_file_name, 
                &shader->vertex_file_contents, 
                &shader->vertex_file_length);
        }

        if (shader->fragment_file_name == NULL) {
            shader->fragment_file_contents = NULL;
            shader->fragment_file_length = 0;
        }
        else {
            file_to_string(shader->fragment_file_name, 
                &shader->fragment_file_contents, 
                &shader->fragment_file_length);
        }
    }
}

void* shader_component_create(entity_t entity, void* data) {
    (void)(data);
    (void)(entity);
    
    shader_component* shader_component = malloc(sizeof(shader_component));
    shader_component->shader = &shaders[SHADER_DEFAULT];

    return shader_component;
}

shader_component* shader_component_get(entity_t entity) {
    return component_get(entity, COMPONENT_SHADER);
}

void shader_component_destroy(entity_t entity, void* data) {
    (void)(entity);
    (void)(data);
}

void shader_component_cleanup() {
    for (size_t i = 0; i < NUM_SHADERS; i++) {
        shader* shader = &shaders[i];
        if (shader->vertex_file_contents != NULL) {
            free(shader->vertex_file_contents);
        }
        if (shader->fragment_file_contents != NULL) {
            free(shader->fragment_file_contents);
        }
    }
}