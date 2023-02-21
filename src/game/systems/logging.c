#include "logging.h"

#include <stdio.h>

void logging_graphics_process(float delta) {
    (void)(delta);
}

void logging_physics_process(float delta) {
    (void)(delta);
}

void logging_log(const char* string) {
    printf("%s", string);
}