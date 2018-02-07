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
                //copy_npc_t(npc_last, rogue_npc_master[master_index](x, y));
                npc_last = rogue_npc_master[master_index](x , y);
            } else if (rogue_npc_master[master_index](x, y).quest_id < 0) {
                state = 18; // go to cutscene
                //copy_npc_t(npc_last, rogue_npc_master[master_index](x, y));
                npc_last = rogue_npc_master[master_index](x, y);
            }
            return false;
        } else {
            state = 19; // go to merchant mode
            //copy_npc_t(npc_last, rogue_npc_master[master_index](x, y));
            npc_last = rogue_npc_master[master_index](x, y);
            //cout << "EXPECTED SIZE: " << rogue_npc_master[master_index](x, y).inventory_size << endl;
            printf("EXPECTED SIZE: %d \n", rogue_npc_master[master_index](x,y).inventory_size);
            return false;
        }
    }

    // portals first bc PEMDAS
    if (rogue_portal_master[master_index](x, y).mapid > -1){
        load_map(rogue_portal_master[master_index](x, y).mapid); // load map and set up
        character_x = rogue_portal_master[master_index](x, y).x;  // teleport
        character_y = rogue_portal_master[master_index](x, y).y;
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
    for (int i = 0; i < 1; i++){
        switch(entities[i].type){
            case 0:
                printf("updating entity %d at (%d, %d) \n", i, entities[i].x, entities[i].y);
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
            default:
                break;
        }
    }
}
