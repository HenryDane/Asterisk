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
        num_entities = i;
    }
}

void build_terrain(int sector_x, int sector_y, int sector_s){
    // reset all lists (asteroids, enemies, etc)
    num_entities = 0;
    search_and_build(level_master[level + (sector_s % 4)].tile_dat);
}

void search_and_build(const tile_data * tiledata){
    printf("SECTOR: %d \n", sector_s);

    // init vairables
    bool exists = false;
    int i = 0;

    // search
    for ( ; i < 10; i++){
        printf("Testing %d, %d with %d, %d", tiledata[i].x, tiledata[i].y, sector_x, sector_y);
        if (tiledata[i].x == sector_x && tiledata[i].y == sector_y){
            exists = true;
            printf("FOUND W DESC %d I: %d \n" , tiledata[i].data, i);
            break;
        }
    }
    printf("EXITST: %d \n", ((exists) ? 1 : 0) );

    // create entities
    if (exists){
        printf("EXISTS!! NUM: %d I: %d \n", tiledata[i].num_level_data, i);
        for(int j = 0; j < tiledata[i].num_level_data; j++){
            printf("LOOKING AT J: %d \n", j);
            switch(tiledata[i].flight_data[j].type){
                case 0: // station
                    printf("SPAWN STATION AT X: %d Y: %d \n", tiledata[i].flight_data[j].x, tiledata[i].flight_data[j].y);

                    // create entity listing
                    entities_o[num_entities_o].id = id_entity_last;
                    entities_o[num_entities_o].x = tiledata[i].flight_data[j].x;
                    entities_o[num_entities_o].y = tiledata[i].flight_data[j].y;
                    entities_o[num_entities_o].type = 0;
                    for (int k = 0; k < 16; k++){
                        entities_o[num_entities_o].data[i] = tiledata[i].flight_data[j].data[i];
                    }
                    entities_o[num_entities_o].vx = 0;
                    entities_o[num_entities_o].vy = 0;
                    if (num_entities_o < MAX_ENTITIES) num_entities_o++;
                    id_entity_last++;
                    break;
                case 1: //asteroid
                    printf("SPAWN ASTEROID AT X: %d Y: %d \n", tiledata[i].flight_data[j].x, tiledata[i].flight_data[j].y);

                    for (int m = 0; m < tiledata[i].flight_data[j].num; m++){
                        entities_o[num_entities_o].id = id_entity_last;
                        entities_o[num_entities_o].x = rand() % WIDTH;
                        entities_o[num_entities_o].y = rand() % HEIGHT;
                        entities_o[num_entities_o].type = 1;
                        for (int k = 0; k < 16; k++){
                            entities_o[num_entities_o].data[i] = tiledata[i].flight_data[j].data[i];
                        }
                        entities_o[num_entities_o].vx = (rand() % 5) - 2;
                        entities_o[num_entities_o].vy = (rand() % 5) - 2;
                        if (num_entities_o < MAX_ENTITIES) {
                            num_entities_o++;
                        }
                        id_entity_last++;
                    }
                    break;
                case 2: // enemy
                    printf("SPAWN ENEMY AT X: %d Y: %d \n", tiledata[i].flight_data[j].x, tiledata[i].flight_data[j].y);

                    for (int m = 0; m < tiledata[i].flight_data[j].num; m++){
                        entities_o[num_entities_o].id = id_entity_last;
                        entities_o[num_entities_o].x = tiledata[i].flight_data[j].x;
                        entities_o[num_entities_o].y = tiledata[i].flight_data[j].y;
                        entities_o[num_entities_o].type = 2;
                        for (int k = 0; k < 16; k++){
                            entities_o[num_entities_o].data[i] = tiledata[i].flight_data[j].data[i];
                        }
                        entities_o[num_entities_o].vx = (rand() % 10 > 5) ? -1 : 1;
                        entities_o[num_entities_o].vy = (rand() % 10 > 5) ? -1 : 1;
                        if (num_entities < MAX_ENTITIES) num_entities_o++;
                    }
                    break;
                case 3: // debris
                    printf("SPAWN DEBRIS AT X: %d Y: %d \n", tiledata[i].flight_data[j].x, tiledata[i].flight_data[j].y);

                    for (int m = 0; m < tiledata[i].flight_data[j].num; m++){
                        entities_o[num_entities_o].id = id_entity_last;
                        entities_o[num_entities_o].x = rand() % WIDTH;
                        entities_o[num_entities_o].y = rand() % HEIGHT;
                        entities_o[num_entities_o].type = 3;
                        for (int k = 0; k < 16; k++){
                            entities_o[num_entities_o].data[i] = tiledata[i].flight_data[j].data[i];
                        }
                        entities_o[num_entities_o].vx = 0;
                        entities_o[num_entities_o].vy = 0;
                        if (num_entities_o < MAX_ENTITIES) num_entities_o++;
                        id_entity_last++;
                    }
                    break;
                default:
                    printf("FAILED WITH: %d \n" , tiledata[i].flight_data[j].type);
            }
        }
    } else {
        printf("SPAWINING NOTHING \n");
    }
}
