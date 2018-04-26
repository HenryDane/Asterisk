#include "main.h"
#include "display.h"
#include "levels.h"
#include <stdio.h>

void load_map(int index){
    master_index = index;
    cached_map = rogue_map_master[index].mapdat;
    character_x = rogue_map_master[index].coord.x;
    character_y = rogue_map_master[index].coord.y;
    cached_map.num_entities = rogue_map_master[index].mapdat.num_entities;
    num_entities = rogue_map_master[index].mapdat.num_entities;
    printf("Loading map %d with start of (%d, %d) and %d entities \n", index, rogue_map_master[index].coord.x, rogue_map_master[index].coord.y, rogue_map_master[index].mapdat.num_entities);
    int i = 0;
    for ( ; i < rogue_map_master[index].mapdat.num_entities; i++){
        //entities[i] = rogue_map_master[index].mapdat.entities[i];
        entity_t entity_tmp;
        rogue_enemy_master[index](&entity_tmp, i);
        if (entity_tmp.id >= 0){
            entities[i] = entity_tmp;
        } else {
            printf("Breaking out of entity loading at index %d \n", i);
            break;
        }
    }

    if (num_entities - 1 > i) {
        printf("WARN: num_entities - 1 > i! Resolving . . . \n");
        num_entities = i + 1;
    }
}

void load_teleport(int index, int x, int y){
    master_index = index;
    cached_map = rogue_map_master[index].mapdat;
    character_x = x;
    character_y = y;
    cached_map.num_entities = rogue_map_master[index].mapdat.num_entities;
    num_entities = rogue_map_master[index].mapdat.num_entities;
    printf("Loading map %d with start of (%d, %d) and %d entities \n", index, rogue_map_master[index].coord.x, rogue_map_master[index].coord.y, rogue_map_master[index].mapdat.num_entities);
    int i = 0;
    for ( ; i < rogue_map_master[index].mapdat.num_entities; i++){
        //entities[i] = rogue_map_master[index].mapdat.entities[i];
        entity_t entity_tmp;
        rogue_enemy_master[index](&entity_tmp, i);
        if (entity_tmp.id >= 0){
            entities[i] = entity_tmp;
        } else {
            printf("Breaking out of entity loading at index %d \n", i);
            break;
        }
    }

    if (num_entities - 1 > i) {
        printf("WARN: num_entities - 1 > i! Resolving . . . \n");
        num_entities = i + 1;
    }
}

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
