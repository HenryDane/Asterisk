#include "main.h"
#include "display.h"
#include "levels.h"
#include <stdio.h>

void build_terrain(int sector_x, int sector_y, int sector_s){
    // reset all lists (asteroids, enemies, etc)
    num_entities = 0;

    // search for data and build
    switch(level){
        case 0:
            printf("LEVEL 0 \n"); //cout << "LEVEL 0" << endl;
            switch(sector_s){
                case 0:
                    search_and_build(level_0_0_tile_data);
                    break;
                case 1:
                    search_and_build(level_0_1_tile_data);
                    break;
                case 2:
                    search_and_build(level_0_2_tile_data);
                    break;
                case 3:
                    search_and_build(level_0_3_tile_data);
                    break;
                default:
                    //cout << "FAULT" << endl;
                    printf("FAULT /n");
            }
            break;
    }
}
