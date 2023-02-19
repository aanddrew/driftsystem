#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

typedef void (*PhysicsFunc)(float);
typedef void (*GraphicsFunc)(float);

enum SYSTEM_ID {
    LOGGING_SYSTEM,
    NUM_SYSTEMS
};


#endif