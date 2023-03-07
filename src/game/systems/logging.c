#include "logging.h"

#include <stdio.h>
#include <stdarg.h>

void logging_graphics_process(float delta) {
    (void)(delta);
}

void logging_physics_process(float delta) {
    (void)(delta);
}

void _logging_log(const char* string, ...) {
    va_list args;
    va_start(args, string);

    vprintf(string, args);
}

void _logging_error(const char* string, ...) {
    va_list args;
    va_start(args, string);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, string, args);
}