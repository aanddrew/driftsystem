#include "server.h"

#include <ecs/component.h>  
#include <ecs/entity.h>
#include <ecs/system.h>

int servermain(int argc, char* argv[]) {
    (void)(argc);
    (void)(argv);

    components_init();

    components_cleanup();

    return 0;
}