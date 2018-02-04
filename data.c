#include <stdbool.h>
#include "main.h"
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} pixel;

#ifndef USE_SDCC

#include <SFML/Graphics.h>

bool build_game_data(){
    pixel color_key[32];
    const uint8_t * pixptr;

    // reads in game file data
    sfImage * image = sfImage_create(32, 1);
    sfImage_createFromFile("artifact/map_key.png");
    if (!image){
        printf("failed to load color file \n");
        return false;
    }

    sfVector2u size = sfImage_getSize(image);
    printf("size x: %d, y: %d \n", size.x, size.y );

    pixptr = sfImage_getPixelsPtr(image);

    for (int i = 0; i < 32; i++){
        color_key[i] = sfImage_getPixel(image, i, 1);
        printf("[%d, %d, %d] (%d)");
    }
    printf("\nloaded colors \n");

    image = sfImage_createFromFile("artifact/map_test_1.png");
    if (!image){
        printf("failed to load map file \n");
        return false;
    }

    size = sfImage_getSize(image);
    printf("size x: %d, y: %d \n", size.x, size.y );

    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 32; j++){
            sfColor search_color = sfImage_getPixel(image, i, j);
            int search_result = 0;
            for (int k = 0; k < 32; k++){
                if (sfColor_toInteger(color_key[i]) == sfColor_toInteger(search_color)) {
                    search_result = k;
                    break;
                }
            }
            printf("found color %d at %d, %d \n", search_result, i, j);
            rogue_map_master[2].mapdat.tile_type[i + j * 32] = search_result;
        }
    }

    // loop for reading game data
    return true;
}

#endif
