#include "main.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} coord;

void copy_npc_t(npc_t a, npc_t t){
    a.health = t.health;
    a.id = t.id;
    a.inventory_size = t.inventory_size;
    for (int i = 0; i < t.inventory_size; i++){
        a.inventory[i] = t.inventory[i];
    }
    a.is_ablaze = t.is_ablaze;
    a.is_alive = t.is_alive;
    a.is_merchant = t.is_merchant;
    a.quest_id = t.quest_id;
    a.type = t.type;
    a.x = t.x;
    a.y = t.y;
}

bool check_next_step(int x, int y){
    if (rogue_npc_master[master_index](x, y).id > 0) {
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

    if ( cached_map.tile_type[ x + cached_map.w * y ] < -1){
        master_index = (- cached_map.tile_type[ x + cached_map.w * y ]) - 1;
        printf("Triggered portal at %d, %d : %d \n", x, y, cached_map.tile_type[ x + cached_map.w * y ]);
        load_map(master_index);
        return true;
    }

    // handle map stuffs
    switch (cached_map.tile_type[ x + cached_map.w * y ]){
        case 4:
            health -= (rand() % 150 + 400);
            return true;
        case 3:
            health -= (rand() % 100 + 200);
            return true;
        case 1:
        case 2:
        case 6:
            return false;
        case 5:
            credits += (rand() % 3);
        default:
            return true;
    }

    // portal
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
        }
    }
}
