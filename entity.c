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

    bool npc_ok = true;
    if (num_hidden_npcs > 0){
        for (int i = 0; i < num_hidden_npcs; i++){
            if (hidden_npcs[i] == rogue_npc_master[master_index](x, y).id){
                npc_ok = false;
                printf("found hidden NPC at %d, %d with id of %d at index %d \n", x, y, rogue_npc_master[master_index](x, y).id, i);
                break;
            }
        }
    }

    if (rogue_npc_master[master_index](x, y).id > 0 && npc_ok) {
        printf("Found NPC! Id: %d Merchant: %d Quest: %d\n", rogue_npc_master[master_index](x, y).id, rogue_npc_master[master_index](x, y).is_merchant, rogue_npc_master[master_index](x, y).quest_id );
        if (!rogue_npc_master[master_index](x, y).is_merchant){
            if (rogue_npc_master[master_index](x, y).quest_id > 0 ){
                //state = 17;  // go to NPC screen for quest/ talk screen
                npc_last = rogue_npc_master[master_index](x , y);
                if (searchQuest(npc_last.quest_id)){
                    state = 28; // we have our quest. Here we go!!

                    int index = 0;
                    for ( ; index < num_active_quests; index++){
                        if (quest_a_registry[index].quest.id == quest_registry[npc_last.quest_id].id) break;
                    }

                    // exit test
                    if (quest_a_registry[index].position >= quest_a_registry[index].quest.stages){
                        printf("(Index %d): At position, %d of %d stages \n",  index,  quest_a_registry[index].position, quest_a_registry[index].quest.stages);
                        printf("Done with quest \n");
                        printf("QUEST DATA -> ID: %d TITLE: %s ISSUER: %s NUM_STAGES: %d EXP_REWARD: %d CREDIT_REWARD: %d \n", index, quest_a_registry[index].quest.title, quest_a_registry[index].quest.issuer, quest_a_registry[index].quest.stages, quest_a_registry[index].quest.exp_reward, quest_a_registry[index].quest.credit_reward);
                        printf("NUM_ACTIVE_QUESTS: %d", num_active_quests);
                        state = 30; // quest complete
                        credits += quest_a_registry[index].quest.credit_reward;
                        experience += quest_a_registry[index].quest.exp_reward;
                        score += quest_a_registry[index].quest.exp_reward + quest_a_registry[index].quest.credit_reward;
                        // ADD ITEM REWARD
                        num_active_quests--;
                    } else {
                        // logic for incrementing quest position goes here
                        printf("Incrementing??? \n");
                        printf("QUEST DATA -> ID: %d TITLE: %s ISSUER: %s NUM_STAGES: %d EXP_REWARD: %d CREDIT_REWARD: %d \n", index, quest_a_registry[index].quest.title, quest_a_registry[index].quest.issuer, quest_a_registry[index].quest.stages, quest_a_registry[index].quest.exp_reward, quest_a_registry[index].quest.credit_reward);
                        quest_a_registry[index].position++;
                        /*
                        switch (quest_a_registry[npc_last.quest_id].quest.verify_id[quest_a_registry[npc_last.quest_id].position]){
                            case 0: // nothing
                                printf("initial position . . . %d \n",quest_a_registry[npc_last.quest_id].position );
                                quest_a_registry[npc_last.quest_id].position++;
                                printf("final position . . . %d \n",quest_a_registry[npc_last.quest_id].position );
                                break;
                            default:
                                printf("Unable to continue with verification value %d \n", quest_a_registry[npc_last.quest_id].quest.verify_id[quest_a_registry[npc_last.quest_id].position]);
                        }
                        */
                    }
                } else {
                    state = 27; // go through quest add interaction
                }
            } else if (rogue_npc_master[master_index](x, y).quest_id < 0) {
                state = 15; // go to cutscene
                npc_last = rogue_npc_master[master_index](x, y);
                current_cutscene = cutscene_registry[-rogue_npc_master[master_index](x, y).quest_id];
            }
            return false;
        } else {
            state = 19; // go to merchant mode
            npc_last = rogue_npc_master[master_index](x, y);
            score ++;
            printf("EXPECTED SIZE: %d \n", rogue_npc_master[master_index](x,y).inventory_size);
            if (npc_ok) {
                return false; // no moving if npc
            } else {
                return true; // fine to move bc "there isnt one"
            }
        }
    }

    // portals first bc PEMDAS
    if (rogue_portal_master[master_index](x, y).mapid > -1){
        if (rogue_portal_master[master_index](x, y).x >= 0){
            load_teleport(rogue_portal_master[master_index](x, y).mapid, rogue_portal_master[master_index](x, y).x, rogue_portal_master[master_index](x, y).y ); // load map and set up
            printf("Updating player to %d, %d\n", rogue_portal_master[master_index](x, y).x, rogue_portal_master[master_index](x, y).y );
            return false;
        } else {
            build_terrain(- rogue_portal_master[master_index](x, y).x, - rogue_portal_master[master_index](x, y).y, rogue_portal_master[master_index](x, y).mapid);
            printf("Hit a dock!");
            state = 4; // wooooo space
            return false;
        }
    }

    // handle map stuffs
    switch (cached_map.tile_type[ x + cached_map.w * y ]){
        case 1:
        case 3:
        case 4:
        case 8:
        case 9:
            if (npc_ok){
                return false;
            } else {
                return true;
            }
        case 6:
            health -= (rand() % 100) + 300; // take fire damage
            score += 4;
        default:
            return true;
    }

    return true;
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
                    score += 10;
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
                        int k = 0;
                        int m = 0;

                        // mark entities
                        entities[i].id = -1034;
                        entities[j].id = -1035;

                        for (m = 0; m < num_entities; m++){
                            if (entities[m].id == -1034){
                                break;
                            }
                        }
                        for (int k = m; k < num_entities - 1; k++){
                            entities[k] = entities[k + 1];
                        }
                        num_entities--;

                        for (m = 0; m < num_entities; m++){
                            if (entities[m].id == -1035){
                                break;
                            }
                        }
                        for (int k = m; k < num_entities - 1; k++){
                            entities[k] = entities[k + 1];
                        }
                        num_entities--;

                        score += 130;
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
                if (rand() % 100 < 4){
                    for (int k = i; k < num_entities; k++){
                        entities[k] = entities[(k + 1 < num_items) ? k + 1 : k];
                    }
                    num_entities--;
                }
                break;
            case 11:
                // map-defined, does not move
                break;
            case 12:
                // mask self with NPC when collided (i.e. for a cutscene / quest / something )
                break;
            default:
                // something should be done for special bosses (IE Quest-created enemies )
                handle_quest_entities(entities[i].type);
                break;
        }
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
                    //state = -2;
                    //return;
                }
                printf("ID: %d TYPE: %d X: %d Y: %d CX: %d CY: %d", entities_o[i].id, entities_o[i].type, entities_o[i].x, entities_o[i].y, character_x, character_y);
                if (entities_o[i].x == ship_x && entities_o[i].y == ship_y && entities_o[i].type == 0){
                    printf("Docking! \n");
                    state = 16;
                    load_map(entities_o[i].vx);
                    return;
                }
            } else {
                // do nothing?
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
        // printf("TIME CHARACTER WAS %d \n", time_character);
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
