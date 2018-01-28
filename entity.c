#include "main.h"
#include "terrain.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
//using namespace std;

typedef struct {
    int x;
    int y;
} coord;

void fire_missile(int ix, int iy, int vx, int vy, int type){
//    cout << "FIRED MISSILE" << endl;
    printf("FIRED MISSILE \n");
    const char* dat = "!!!";
    entities[num_entities].type = type;
    entities[num_entities].x = ix;
    entities[num_entities].y = iy;
    for (int k = 0; k < 3; k++){
        entities[num_entities].data[k] = dat[k];
    }
    entities[num_entities].id = id_entity_last;
    entities[num_entities].vx = vx;
    entities[num_entities].vy = vy;
    num_entities++;
    id_entity_last++;
}

coord enemy_think_1(int address){
    // roll to fire missile
    if (rand() % 10 < 5){
        // compute missile direction
        coord m = {(ship_x > entities[address].x) ? 1 : -1 , (ship_y > entities[address].y) ? 1 : -1};

        // add missile
        fire_missile(entities[address].x, entities[address].y, m.x, m.y, 5);
    }

    //return dx, dy
    coord d = {(ship_x > entities[address].x) ? -1 : 1 , (ship_y > entities[address].y) ? 1 : -1};
    coord n = { 0, 0};
    return ( (((unsigned) (ship_x - entities[address].x)) < 10) && (((unsigned) (ship_y - entities[address].y)) < 10)) ? d : n;
}

void update_entities(){
    // draw entities
    if (time_entity > TIME_ENTITY ){
        time_entity = 0;
        for (int i = 0; i < num_entities; i++){
            if (entities[i].type != 5 && entities[i].type >= 0){
                if (entities[i].x >= WIDTH - 1 || entities[i].x <= 0) entities[i].vx = - entities[i].vx;
                if (entities[i].y >= HEIGHT - 1 || entities[i].y <= 0) entities[i].vy = - entities[i].vy;
                if (entities[i].type == 2){
                    coord t = enemy_think_1(i);
                    entities[i].x += t.x;
                    entities[i].y += t.y;
//                    cout << "TICKED ENTITY: " << i << " WITH VX: " << t.x << " WITH VY: " << t.y << endl;
                    printf("TICKED ENTITY %d WITH VX: %d WITH VY: %d /n", i, t.x, t.y);
                } else {
                    entities[i].x += entities[i].vx;
                    entities[i].y += entities[i].vy;
                }

                if (entities[i].x == ship_x && entities[i].y == ship_y && (entities[i].type == 1 || entities[i].type == 3)){
                    //cout << "COLLISION !!";
                    printf("COLLISION \n");
                    state = -2;
                }
            }
        }
    }

    if (time_rocket > TIME_ROCKET){
        time_rocket = 0;
        for (int i = 0; i < num_entities; i++){
            if (entities[i].type == 5){
                if (entities[i].x >= WIDTH + 1 || entities[i].x <= -1) entities[i].type = -10;
                if (entities[i].y >= HEIGHT + 1 || entities[i].y <= -1) entities[i].type = -10;
                entities[i].x += entities[i].vx;
                entities[i].y += entities[i].vy;

                if (entities[i].x == ship_x && entities[i].y == ship_y && entities[i].type == 6){
                    //cout << "COLLISION !!!!";
                    printf("COLLISSION !!!! \n");
                    state = -2;
                }
            }
        }
    }

    // draw character
    int facing_t = facing;
    if (tilted){
        facing_t += 4;
    }
    if (time_character > TIME_CHARACTER){
        time_character = 0;
        fuel--;
        switch(facing_t){
            case 0: ship_y--; break;
            case 1: ship_x++; break;
            case 2: ship_y++; break;
            case 3: ship_x--; break;
            case 4: ship_y--; ship_x++; break;
            case 5: ship_x++; ship_y++; break;
            case 6: ship_y++; ship_x--; break;
            case 7: ship_x--; ship_y--; break;
            default: fuel++; break;
        }

        if (ship_x > WIDTH - 1) ship_x = WIDTH;
        if (ship_x < 0) ship_x = 0;
        if (ship_y > HEIGHT - 1) ship_y = HEIGHT;
        if (ship_y < 0) ship_y = 0;
    }
}

void update_warp_interface(void){
    e1_g = rand() % 9;
    e1_y = 9;
    e2_g = rand() % 9;
    e2_y = 9;
    e3_g = rand() % 9;
    e3_y = 9;
    e4_g = rand() % 9;
    e4_y = 9;
}

void copy_npc_t(npc_t a, npc_t t){
//    npc_t t = rogue_npc_master[master_index](x, y);
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
