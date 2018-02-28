#include "main.h"
#include "display.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} coord;

bool check_next_step(int x, int y){
    // is the player alive?
    if (health < 0){
        state = -2;
        return false;
    }

    if (rogue_npc_master[master_index](x, y).id > 0) {
        printf("Found NPC! Id: %d Merchant: %d Quest: %d\n", rogue_npc_master[master_index](x, y).id, rogue_npc_master[master_index](x, y).is_merchant, rogue_npc_master[master_index](x, y).quest_id );
        if (!rogue_npc_master[master_index](x, y).is_merchant){
            if (rogue_npc_master[master_index](x, y).quest_id > 0 ){
                state = 17;  // go to NPC screen for quest/ talk screen
                npc_last = rogue_npc_master[master_index](x , y);
            } else if (rogue_npc_master[master_index](x, y).quest_id < 0) {
                state = 18; // go to cutscene
                npc_last = rogue_npc_master[master_index](x, y);
            }
            return false;
        } else {
            state = 19; // go to merchant mode
            npc_last = rogue_npc_master[master_index](x, y);
            printf("EXPECTED SIZE: %d \n", rogue_npc_master[master_index](x,y).inventory_size);
            return false;
        }
    }

    // portals first bc PEMDAS
    if (rogue_portal_master[master_index](x, y).mapid > -1){
        load_teleport(rogue_portal_master[master_index](x, y).mapid, rogue_portal_master[master_index](x, y).x, rogue_portal_master[master_index](x, y).y ); // load map and set up
        printf("Updating player to %d, %d", rogue_portal_master[master_index](x, y).x, rogue_portal_master[master_index](x, y).y );
        return false;
    }

    // handle map stuffs
    switch (cached_map.tile_type[ x + cached_map.w * y ]){
        case 1:
        case 3:
        case 4:
        case 8:
        case 9:
            return false;
        case 6:
            health -= (rand() % 100) + 300; // take fire damage
        default:
            return true;
    }
}

void update_entities(){
    for (int i = 0; i < num_entities; i++){
        printf("updating entity %d at (%d, %d) \n", i, entities[i].x, entities[i].y);
        int tile_type = cached_map.tile_type[entities[i].x +(entities[i].y * cached_map.w)];
        switch(entities[i].type){
            case 0: // follower
                if (entities[i].x > character_x){
                    entities[i].x--;
                } else if (entities[i].x < character_x) {
                    entities[i].x++;
                }

                if (entities[i].y > character_y){
                    entities[i].y--;
                } else if (entities[i].y < character_y) {
                    entities[i].y++;
                }
                break;
            case 1: // bullet from character
                if (entities[i].x > cached_map.w || entities[i].x < 0 || entities[i].y > cached_map.h || entities[i].y < 0 ||
                    tile_type == 1 || tile_type == 3 || tile_type == 4 || tile_type == 8 || tile_type == 9) {
                    // delete this entity
                    for (int j = i; j < num_entities; j++){
                        if (j + 1 < num_entities){
                            entities[j] = entities[j + 1];
                        } else {
                            break;
                        }
                    }
                    num_entities--;
                    break;
                }
                entities[i].x += entities[i].vx;
                entities[i].y += entities[i].vy;
                break;
            default:
                break;
        }
    }
}

void load_map(int index){
    master_index = index;
    cached_map = rogue_map_master[index].mapdat;
    character_x = rogue_map_master[index].coord.x;
    character_y = rogue_map_master[index].coord.y;
    cached_map.num_entities = rogue_map_master[index].mapdat.num_entities;
    num_entities = rogue_map_master[index].mapdat.num_entities;
    printf("Loading map %d with start of (%d, %d) and %d entities \n", index, rogue_map_master[index].coord.x, rogue_map_master[index].coord.y, rogue_map_master[index].mapdat.num_entities);
    for (int i = 0; i < rogue_map_master[index].mapdat.num_entities; i++){
        entities[i] = rogue_map_master[index].mapdat.entities[i];
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
    for (int i = 0; i < rogue_map_master[index].mapdat.num_entities; i++){
        entities[i] = rogue_map_master[index].mapdat.entities[i];
    }
}
