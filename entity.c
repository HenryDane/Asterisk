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

    switch (cached_map.tile_type[ x + cached_map.w * y ]){
        case 1:
            return false;
        default:
            return true;
    }
}
