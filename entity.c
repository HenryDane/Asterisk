#include "main.h"
#include "display.h"
#include "map.h"
#include "quest.h"
#include "entity.h"
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
                //state = 17;  // go to NPC screen for quest/ talk screen
                npc_last = rogue_npc_master[master_index](x , y);
                if (searchQuest(npc_last.quest_id)){
                    state = 28; // we have our quest. Here we go!!

                    // where is it in the registry?
                    int i = 0;
                    for ( ; i < num_active_quests; i++){
                        if (quest_a_registry[i].quest.id == npc_last.quest_id) break;
                    }

                    // exit test
                    if (quest_a_registry[i].position >= quest_a_registry[i].quest.stages){
                        printf("Done with quest \n");
                        state = 30; // quest complete
                    } else {
                        // logic for incrementing quest position goes here
                        printf("Incrementing??? \n");
                        switch (quest_a_registry[i].quest.verify_id[quest_a_registry[i].position]){
                            case 0: // nothing
                                quest_a_registry[i].position++;
                                break;
                            default:
                                printf("Unable to continue with verification value %d \n", quest_a_registry[i].quest.verify_id[quest_a_registry[i].position]);
                        }
                    }
                } else {
                    state = 27; // go through quest add interaction
                }
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
        printf("Updating player to %d, %d\n", rogue_portal_master[master_index](x, y).x, rogue_portal_master[master_index](x, y).y );
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
        // printf("updating entity %d at (%d, %d) \n", i, entities[i].x, entities[i].y); // this is v verbose
        int tile_type = cached_map.tile_type[entities[i].x +(entities[i].y * cached_map.w)];
        bool step = true;
        switch(entities[i].type){
            case 3: // bomber
                if (rand() % 10 < 3) {
                    if (abs(character_x - entities[i].x) < 6 && abs(character_y - entities[i].y) < 6){
                        // detonate and delete self
                        printf("DETONATE AND DELETE SELF! \n");
                    }
                }
            case 2: // generic
                // weapon logic
                if (rand() % 10 < 3){
                    entities[num_entities++] = (entity_t) {1432, entities[i].x, entities[i].y, 0, 1, 7};
                }

                step = (rand() % 3 < 2) ? true : false;
            case 0: // follower
                if (step){
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
                }
                break;
            case 7: // enemy byllet
                // check character collision
                if (entities[i].x == character_x && entities[i].y == character_y){
                    health = 0;
                }
            case 1: // bullet from character
                // check for map collisions
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

                // check for entity collisions
                for (int j = 0; j < num_entities; j++){
                    if (entities[i].x == entities[j].x && entities[i].y == entities[j].y && entities[i].id != entities[j].id){
                        for (int k = i; k < num_entities; k++){
                            entities[k] = entities[(k + 1 < num_items) ? k + 1 : k];
                        }
                        num_entities--;

                        for (int k = j; k < num_entities; k++){
                            entities[k] = entities[(k + 1 < num_items) ? k + 1 : k];
                        }
                        num_entities--;
                        break;
                    }
                }

                // update position
                entities[i].x += entities[i].vx;
                entities[i].y += entities[i].vy;
                break;
            case 4: // hunter
                // needs to be advanced idk tho
                break;
            case 6: // barrack door (spawner) (also a portal??)
                if (entities[i].x == character_x && entities[i].y == character_y){
                    load_teleport(entities[i].id, entities[i].vx, entities[i].vy);
                } else {
                    if (rand() % 25 < 3){
                        // spawn a new entity
                        entity_t entity = {rand() % 1000, entities[i].x, entities[i].y, rand() % 2 - 1, rand() % 2 - 1, 4};
                        entities[num_entities++] = entity;
                    }
                }
                break;
            case 9: // rocket
                if (true){ // eat my ass C99
                    entity_t entity = {rand() % 1000, entities[i].x, entities[i].y, 0, 0, 10}; // spawn exhaust
                    entities[num_entities++] = entity;
                }

                entities[i].x += entities[i].vx;
                entities[i].y += entities[i].vy;
                break;
            case 10: // rocket exhaust
                // delete self logic
                if (rand() % 10 < 4){
                    for (int k = i; k < num_entities; k++){
                        entities[k] = entities[(k + 1 < num_items) ? k + 1 : k];
                    }
                    num_entities--;
                }
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


void fire_missile(int ix, int iy, int vx, int vy, int type){
    printf("FIRED MISSILE \n"); //cout << "FIRED MISSILE" << endl;
    const char* dat = "!!!";
    entities_o[num_entities_o].type = type;
    entities_o[num_entities_o].x = ix;
    entities_o[num_entities_o].y = iy;
    for (int k = 0; k < 3; k++){
        entities_o[num_entities_o].data[k] = dat[k];
    }
    entities_o[num_entities_o].id = id_entity_last;
    entities_o[num_entities_o].vx = vx;
    entities_o[num_entities_o].vy = vy;
    num_entities_o++;
    id_entity_last++;
}

coord enemy_think_1(int address){
    // roll to fire missile
    if (rand() % 10 < 5){
        // compute missile direction
        coord m = {(ship_x > entities_o[address].x) ? 1 : -1 , (ship_y > entities_o[address].y) ? 1 : -1};

        // add missile
        fire_missile(entities_o[address].x, entities_o[address].y, m.x, m.y, 5);
    }

    //return dx, dy
    coord d = {(ship_x > entities_o[address].x) ? -1 : 1 , (ship_y > entities_o[address].y) ? 1 : -1};
    coord n = { 0, 0};
    return ( (((unsigned) (ship_x - entities_o[address].x)) < 10) && (((unsigned) (ship_y - entities_o[address].y)) < 10)) ? d : n;
}

void update_entities_o( int time ){
    // draw entities
    if (time_entity_o > TIME_ENTITY ){
        //printf("TIME ENTITY WAS %d \n", time_entity_o);
        time_entity_o = 0;
        for (int i = 0; i < num_entities_o; i++){
            if (entities_o[i].type != 5 && entities_o[i].type >= 0){
                if (entities_o[i].x >= WIDTH - 1 || entities_o[i].x <= 0) entities_o[i].vx = - entities_o[i].vx;
                if (entities_o[i].y >= HEIGHT - 1 || entities_o[i].y <= 0) entities_o[i].vy = - entities_o[i].vy;
                if (entities_o[i].type == 2){
                    coord t = enemy_think_1(i);
                    entities_o[i].x += t.x;
                    entities_o[i].y += t.y;
                    //cout << "TICKED ENTITY: " << i << " WITH VX: " << t.x << " WITH VY: " << t.y << endl;
                    //printf("TICKED ENTITY: %d WITH VX: %d WITH VY: %d \n", i, t.x, t.y);
                } else {
                    entities_o[i].x += entities_o[i].vx;
                    entities_o[i].y += entities_o[i].vy;
                }

                if (entities_o[i].x == ship_x && entities_o[i].y == ship_y && (entities_o[i].type == 1 || entities_o[i].type == 3)){
                    //cout << "COLLISION !!";
                    printf("COLLISION !! \n");
                    state = -2;
                }
            }
        }
    }

    if (time_rocket > TIME_ROCKET){
       // printf("TIME ROCKET WAS %d \n", time_rocket);
        time_rocket = 0;
        for (int i = 0; i < num_entities_o; i++){
            if (entities_o[i].type == 5){
                if (entities_o[i].x >= WIDTH + 1 || entities_o[i].x <= -1) entities_o[i].type = -10;
                if (entities_o[i].y >= HEIGHT + 1 || entities_o[i].y <= -1) entities_o[i].type = -10;
                entities_o[i].x += entities_o[i].vx;
                entities_o[i].y += entities_o[i].vy;

                if (entities_o[i].x == ship_x && entities_o[i].y == ship_y && entities_o[i].type == 6){
                    //cout << "COLLISION !!!!";
                    printf("COLLISION !!!! \n");
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
        printf("TIME CHARACTER WAS %d \n", time_character);
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
