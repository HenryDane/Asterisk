#include "main.h"

void add_module(module_t module){
    if (module < 0){
        printf("Bad module def \n");
        return;
    }

    // test if module is already enabled
    int i = 0;
    int last_free = 0;
    bool found = false;
    for ( ; i < NUM_MODULES_MAX; i++){
        if (modules_enabled[i] <= 0){
            last_free = i;
        }
        if (modules_enabled[i] == module){
            found = true;
            break;
        }
    }

    if (found){
        printf("Module already enabled\n");
        return;
    }

    modules_enabled[last_free] = module; // write changes

    // code to modify game
    switch (module ){
        case 0: // does nothing
            printf("Added nothing module \n");
            break;
        default:
            printf("What module??\n");
    }
}

void remove_module(module_t module){
    // test if module is already enabled
    int i = 0;
    bool found = false;
    for ( ; i < NUM_MODULES_MAX; i++){
        if (modules_enabled[i] == module){
            found = true;
            break;
        }
    }

    if (!found){
        printf("Module not enabled\n");
        return;
    }

    modules_enabled[i] = -1; //remove module

    // code to modify game
    switch (module ){
        case 0: // does nothing
            printf("Removed nothing module \n");
            break;
        default:
            printf("What module??\n");
    }
}
